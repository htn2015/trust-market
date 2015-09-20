//
// Created by Andrei on 15-09-20.
//

#ifndef HTN2015_NODE_H
#define HTN2015_NODE_H

#include <iostream>
#include <map>
#include "KeyPair.h"
#include "Graph.h"
#include "Trust.h"

struct Node {
    int id;

    map<int, Trust> neighbours;
    Graph* graph;

    Node();
    ~Node();

    void scan();

};


#endif //HTN2015_NODE_H
