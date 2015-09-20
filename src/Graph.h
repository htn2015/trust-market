
#ifndef HTN2015_NODE_H
#define HTN2015_NODE_H

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
	Graph(vector<Graph*>&, map<int, Trust>&, int);
};


#endif //HTN2015_NODE_H
