#pragma once

#include <iostream>
#include <map>

#include "Node.h"
#include "KeyPair.h"
#include "Graph.h"

using namespace std;


struct Client : public Node {
    KeyPair* keypair;

    map<int, Trust> known_vendors;

    Client();
    ~Client();

    void scan();

};