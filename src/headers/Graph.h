#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "Node.h"

#include "Trust.h"

using namespace std;

struct Node;

struct Edge {
	Node& from;
	Node& to;
	Trust t;
};

class Graph {
public:
	int key;
	unordered_map<int, Node> nodes;
	unordered_map<int, Edge> edges;

	Graph();
	//Graph(vector<Graph*>&, map<int, Trust>&, int);
};
