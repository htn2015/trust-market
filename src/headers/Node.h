#pragma once

#include <iostream>
#include <map>
#include "KeyPair.h"
#include "Graph.h"
#include "Trust.h"

struct Node {
    long id;

    map<int, Trust> neighbours;
    Graph* perception;

    Node();
    ~Node();

    void scan();

};
