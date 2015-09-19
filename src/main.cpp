#include <iostream>

#include "Socket.h"
#include "Client.h"

using namespace std;

int main(int argc, char* argv[]) {

    if( argc > 1 && strcmp(argv[1], "listen") == 0 ) {
        Socket::listen();
    }
    else if( argc > 2 && strcmp(argv[1], "emit") == 0 ) {
        switch(argc) {
            case 3 :
                Socket::emit(argv[2]);
                break;
            case 4 :
                Socket::emit(argv[2], argv[3]);
                break;
            case 5 :
                Socket::emit(argv[2], argv[3], argv[4]);
                break;
        }
    }

}