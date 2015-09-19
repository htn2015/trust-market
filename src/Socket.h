#ifndef HTN2015_SOCKET_H
#define HTN2015_SOCKET_H

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "666"

#include <iostream>
#include <string>
#include "vendor/socket/server.h"
#include "vendor/socket/client.h"
#include "vendor/socket/tcp.h"

using namespace std;

namespace Socket {

    void listen();
    void listen(string port);
    string receive(string message);

    void emit(string message);
    void emit(string message, string ip);
    void emit(string message, string ip, string port);

};


#endif //HTN2015_SOCKET_H
