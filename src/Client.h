#ifndef HTN2015_CLIENT_H
#define HTN2015_CLIENT_H

#include <iostream>
#include <fstream>

#include "KeyPair.h"
#include "Graph.h"

using namespace std;

bool is_file(const char*);

class Client {

protected:

    long id;
    //KeyPair keypair;
    //Graph graph;

public:

    Client();

    void scan();

};


#endif //HTN2015_CLIENT_H
