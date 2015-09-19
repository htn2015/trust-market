#include "Socket.h"

void Socket::listen() {
    Socket::listen(DEFAULT_PORT);
}

void Socket::listen(string port) {

    cout << "Listening on 127.0.0.1:" << port << endl;

    tcp::server *s = new tcp::server;


    s->set_read_callback(Socket::receive);
    s->listen("127.0.0.1", port);

    while(1);

}

string Socket::receive(string message) {
    cout << message << endl;
    return message;
}


void Socket::emit(string message) {
    Socket::emit(message, DEFAULT_IP, DEFAULT_PORT);
}


void Socket::emit(string message, string ip) {
    Socket::emit(message, ip, DEFAULT_PORT);
}

void Socket::emit(string message, string ip, string port) {
    tcp::client c;

    c.connect(ip, port);

    while(c.connected()) {
        cout << "HERE" << endl;

        c.write("data_write\n");
        c.send();
        std::cout << c.readline();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
