#include "Client.h"

bool is_file(const char *fileName)
{
    std::ifstream file(fileName);
    return file.good();
}

Client::Client() {

    if( !is_file("pub") || !is_file("sec") ) {
        cout << "HERE" << endl;
    }

}