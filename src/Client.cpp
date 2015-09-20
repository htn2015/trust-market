#include "Client.h"

Trust make_trust(float a, float b, float c) {
    Trust t(a, b, c);
    return t;
}

Client::Client() {
    this->keypair = new KeyPair;

    ifstream nFile("neighbours");
    stringstream nStream;
    int i;
    float a, b, c;
    string line;

    while ( getline (nFile,line) ) {
        nStream << line << '\n';
        nStream >> i >> a >> b >> c;
        this->neighbours.insert(make_pair(i, make_trust(a, b, c)));
    }

    ifstream kFile("known_vendors");
    stringstream kStream;

    while ( getline (kFile,line) ) {
        kStream << line << '\n';
        kStream >> i >> a >> b >> c;
        this->known_vendors.insert(make_pair(i, make_trust(a, b, c)));
    }
}

Client::~Client() {
    delete this->keypair;
}