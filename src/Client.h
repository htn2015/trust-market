#ifndef HTN2015_CLIENT_H
#define HTN2015_CLIENT_H

#include <iostream>
#include <map>

#include "KeyPair.h"
#include "Graph.h"

using namespace std;


struct Client {
    int id;
    KeyPair* keypair;

    map<int, Trust> neighbours, known_vendors;
    Graph* graph;


    Client();
    ~Client();

    void scan();

};


#endif //HTN2015_CLIENT_H
