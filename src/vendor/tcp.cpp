/*
 * socket
 * Copyright (C) log2 2013 - Present <aaron.hebert@log2.co>
 *
 * log2sockets is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * log2sockets is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <netdb.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <memory>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include "tcp.h"
#include "server.h"

namespace tcp {

    char EOL = '\n';

    socket::socket(const socket& orig) {
    }

    socket::~socket() {
        reset();
    }

    socket::socket(std::string key, auth auth_) :
    lock_interval_(10) {
        reset();
        auth_type_ = auth_;

        switch (auth_) {
            case auth::MD5:
                init_md5(key);
                break;
            default: break;
        }
    }

    void socket::init_md5(const std::string &key) {
        md5_key_ = key;
        md5_hash_.reset(md5(key));
    }

    void socket::ip_endpoint(std::shared_ptr<ip_point> &ep) {
        ip_endpoint_ = ep; //std::make_shared<ip_endpoint>(*ep);
    }

    void socket::reset(void) {
        if (ip_endpoint_.get() == nullptr) return;

        if (ip_endpoint_->socket_ > 0)
            close(ip_endpoint_->socket_);
        memset(&ip_endpoint_->hints, 0, sizeof (addrinfo));
    }

    /** Sets server info.
     *
     * sets server info for the server we are connecting to.
     * this must be called before anything.
     */
    bool socket::get_addr_info(const std::string host, const std::string port) {
        ip_endpoint_->hints.ai_family = AF_UNSPEC; // ipv4 or ipv6
        ip_endpoint_->hints.ai_socktype = SOCK_STREAM; // tcp
        ip_endpoint_->hints.ai_flags = AI_PASSIVE;
        ip_endpoint_->hints.ai_protocol = 0;
        ip_endpoint_->hints.ai_canonname = nullptr;
        ip_endpoint_->hints.ai_addr = nullptr;
        ip_endpoint_->hints.ai_next = nullptr;
        ip_endpoint_->results = 0;

        // man getaddrinfo(3)
        int s = getaddrinfo(host.c_str(), port.c_str(),
                &ip_endpoint_->hints,
                &ip_endpoint_->results);

        if (s != 0) {
            syslog(LOG_DEBUG, "get_addr_info: %s", gai_strerror(s));
            return false;
        }

        return true;
    }

    /** Creates socket and connects.
     *
     * creates socket and initiates tcp connection.
     */
    bool socket::connect(const std::string host, const std::string port) {
        if (!get_addr_info(host, port)) return false;
        if (!ip_endpoint_->results) return false;

        bool rc(false);

        // find a suitable interface
        for (ip_endpoint_->rp = ip_endpoint_->results;
                ip_endpoint_->rp != nullptr;
                ip_endpoint_->rp = \
                    ip_endpoint_->rp->ai_next) {

            ip_endpoint_->socket_ = ::socket(ip_endpoint_->rp->ai_family,
                    ip_endpoint_->rp->ai_socktype,
                    ip_endpoint_->rp->ai_protocol);
            if (ip_endpoint_->socket_ == -1)
                continue;

            // attempt to connect
            if (::connect(ip_endpoint_->socket_,
                    ip_endpoint_->rp->ai_addr,
                    ip_endpoint_->rp->ai_addrlen) != -1) {

                // set options
                int option = 1;
                setsockopt(ip_endpoint_->socket_,
                        SOL_SOCKET, SO_REUSEADDR,
                        (char *) &option, sizeof (option));

                rc = true;

                syslog(LOG_DEBUG, "connection to %s OK", host.c_str());

                // success
                break;
            }

            close(ip_endpoint_->socket_);
        }

        if (ip_endpoint_->rp == nullptr) {
            syslog(LOG_DEBUG, "unable to allocate interface to destination host");
            return false;
        }

        // free results
        freeaddrinfo(ip_endpoint_->results);

        // open stream for write
        if (nullptr == (ip_endpoint_->tx = \
                fdopen(ip_endpoint_->socket_, "w"))) {

            close(ip_endpoint_->socket_);
            syslog(LOG_DEBUG, "unable to open TX stream");
        } else rc = true;

        // open stream for read
        if (nullptr == (ip_endpoint_->rx = \
                fdopen(ip_endpoint_->socket_, "r"))) {

            close(ip_endpoint_->socket_);
            syslog(LOG_DEBUG, "unable to open RX stream");
        } else rc = true;

        return rc;
    }

    void socket::disconnect(void) {
        close(ip_endpoint_->socket_);
        if (ip_endpoint_->tx)
            fclose(ip_endpoint_->tx);
        if (ip_endpoint_->rx)
            fclose(ip_endpoint_->rx);

        ip_endpoint_->rx = nullptr;
        ip_endpoint_->tx = nullptr;
    }

    /** Resize tx socket buffer size.
     */
    bool socket::tx_buff_size(const size_t &size) {

        ip_endpoint_->tx_buffer_size = size;
        bool ret_val(false);
        int option(size);

        ret_val = !setsockopt(ip_endpoint_->socket_,
                SOL_SOCKET, SO_SNDBUF,
                (char *) &option, sizeof (option));

        return ret_val;
    }

    /** Resize rx socket buffer size.
     */
    bool socket::rx_buff_size(const size_t &size) {

        ip_endpoint_->rx_buffer_size = size;
        bool ret_val = false;
        int option = size;

        ret_val = !setsockopt(ip_endpoint_->socket_,
                SOL_SOCKET, SO_RCVBUF,
                (char *) &option, sizeof (option));

        return ret_val;
    }

    /** Check for stream == 'nullptr' and socket fd == 0.
     *
     * if either FILE stream == nullptr return false.
     * if socket == 0 return false.
     *
     * testing feof() will cause deadlock if
     * socket is no longer valid causing the thread to hang.
     * using feof_unlocked() to remedy locking; this may require
     * mutex but i believe that this is called from a single thread.
     */
    bool socket::connected(void) {
        if (!ip_endpoint_->connected()) {
            syslog(LOG_DEBUG,
                    "can not read/write, no stream available");
            return false;
        }

        return true;
    }

    /** Read from rx stream.
     *
     * calls fread() on rx stream.
     */
    std::size_t socket::read(void *data, const size_t size,
            const size_t count) {

        if (!connected()) return tcp::EOL;

        this->lock();
        std::size_t size_ = fread(data, size, count, ip_endpoint_->rx);
        this->unlock();

        return size_;
    }

    std::string socket::readline(void) {
        if (!connected()) return std::string((const char *) &tcp::EOL);

        std::string read_string;

        do {
            read_string += this->read8();
        } while (read_string.back() != tcp::EOL);

        return read_string;
    }

    /** Read single unsigned char from rx stream.
     */
    uint8_t socket::read8(void) {
        if (!connected()) return tcp::EOL;
        uint8_t u8 = 0;
        this->read(&u8, sizeof (uint8_t), 1);
        return u8;
    }

    uint16_t socket::read16(void) {
        if (!connected()) return tcp::EOL;
        uint16_t u16 = 0;
        this->read(&u16, sizeof (uint16_t), 1);
        return u16;
    }

    uint32_t socket::read32(void) {
        if (!connected()) return tcp::EOL;
        uint32_t u32 = 0;
        this->read(&u32, sizeof (uint32_t), 1);
        return u32;
    }

    uint64_t socket::read64(void) {
        if (!connected()) return tcp::EOL;
        uint64_t u64 = 0;
        this->read(&u64, sizeof (uint64_t), 1);
        return u64;
    }

    /* must delete[] returned array
     */
    uint128_t socket::read128(void) {
        if (!connected()) return nullptr;
        uint64_t *u128 = new uint64_t[2];
        this->read(u128, sizeof (uint64_t) * 2, 1);
        return u128;
    }

    size_t socket::write(const uint8_t *bytes, size_t length) {
        if (!connected()) return tcp::EOL;
        size_t write_ = this->write(bytes, sizeof (uint8_t), length);
        return write_;
    }

    /** Write tx stream.
     *
     * calls fwrite() on tx stream.
     */
    size_t socket::write(const void *data, size_t size, size_t count) {
        if (!connected()) return tcp::EOL;
        this->lock();
        size_t write_ = fwrite(data, size, count,
                ip_endpoint_->tx);
        this->unlock();

        return write_;
    }

    /** Write tx stream.
     *
     * calls fwrite() on tx stream.
     */
    size_t socket::write(std::string str) {
        if (!connected()) return tcp::EOL;
        size_t write_ = this->write(str.c_str(), sizeof (char),
                str.length());

        return write_;
    }

    size_t socket::write32(uint8_t byte1, uint8_t byte2, uint8_t byte3,
            uint8_t byte4) {
        if (!connected()) return tcp::EOL;

        this->lock();
        size_t write_ = fprintf(ip_endpoint_->tx,
                "%c%c%c%c", byte1, byte2, byte3, byte4);
        this->unlock();

        return write_;
    }

    size_t socket::write128(uint128_t bytes16) {
        if (!connected()) return tcp::EOL;
        size_t write_ = this->write((uint8_t *) bytes16,
                sizeof (uint64_t) * 2);
        return write_;
    }

    size_t socket::write64(uint64_t bytes8) {
        if (!connected()) return tcp::EOL;
        size_t write_ = this->write((uint8_t *) & bytes8,
                sizeof (uint64_t));
        return write_;
    }

    size_t socket::write32(uint32_t bytes4) {
        if (!connected()) return tcp::EOL;
        size_t write_ = this->write((uint8_t *) & bytes4, sizeof (uint32_t));
        return write_;
    }

    size_t socket::write16(uint16_t bytes2) {
        if (!connected()) return tcp::EOL;
        size_t write_ = this->write((uint8_t *) & bytes2, sizeof (uint16_t));
        return write_;
    }

    size_t socket::write24(uint8_t byte1, uint8_t byte2, uint8_t byte3) {
        if (!connected()) return tcp::EOL;
        this->lock();
        size_t write_ = fprintf(ip_endpoint_->tx,
                "%c%c%c", byte1, byte2, byte3);
        this->unlock();
        return write_;
    }

    /** Format data to tx stream.
     *
     * calls fprintf() on tx stream.
     */
    size_t socket::write16(uint8_t byte1, uint8_t byte2) {
        if (!connected()) return tcp::EOL;
        this->lock();
        size_t write_ = fprintf(ip_endpoint_->tx,
                "%c%c", byte1, byte2);
        this->unlock();
        return write_;
    }

    size_t socket::write8(uint8_t byte1) {
        if (!connected()) return tcp::EOL;
        size_t write_ = this->write(&byte1, sizeof (uint8_t));
        return write_;
    }

    /** Flush (send data and clear buffer) tx stream.
     *
     * calls fflush() on tx stream to send data
     * and empty buffer.
     */
    int socket::tx_flush(void) {
        if (!connected()) return EOF;

        this->lock();
        int rc = fflush(ip_endpoint_->tx);
        this->unlock();

        return rc;
    }

    /** Flush (clear buffer) rx stream.
     *
     * calls fflush() on rx stream to send data
     * and empty buffer.
     */
    int socket::rx_flush(void) {
        if (!connected()) return EOF;

        this->lock();
        int rc = fflush(ip_endpoint_->rx);
        this->unlock();

        return rc;
    }
}