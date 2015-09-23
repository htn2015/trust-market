#pragma once

#include <iostream>
#include <map>
#include "KeyPair.h"
#include "Graph.h"
#include "Trust.h"

struct Graph;

struct Node {
    long id;

    map<int, Trust> neighbours;
    Graph* graph;

    Node();
    ~Node();

    void scan();

};
