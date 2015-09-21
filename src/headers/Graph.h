#pragma once

#include <vector>
#include <map>
#include <set>

#include "Trust.h"

using namespace std;

class Graph {
public:
	int key;
	set<int> keys;
	map<pair<int, int>, Trust> edges;

	Graph();
	//Graph(vector<Graph*>&, map<int, Trust>&, int);
};
