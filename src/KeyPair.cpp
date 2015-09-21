#include "headers/KeyPair.h"


bool is_file(const char *fileName) {
    std::ifstream file(fileName);
    return file.good();
}

KeyPair::KeyPair() {
    if( !is_file("rsa") || !is_file("rsa.pub") ) {
        this->gen();
    }

    ifstream pubFile("rsa.pub");
    stringstream pubStream;
    string line;

    while ( getline (pubFile,line) ) {
        pubStream << line << '\n';
    }

    this->pub = pubStream.str();

    pubFile.close();

    ifstream secFile("key.pub");
    stringstream secStream;

    while ( getline (secFile,line) ) {
        pubStream << line << '\n';
    }

    this->sec = secStream.str();

    secFile.close();
}

void KeyPair::gen() {
    system("ssh-keygen -t rsa -b 1024 -I rsa -q -f rsa -P \"\"");
}

string KeyPair::encrypt(string msg) {
    return "";
}

string KeyPair::decrypt(string msg, string sec) {
    return "";
}