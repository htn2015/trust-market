
#ifndef HTN2015_NODE_H
#define HTN2015_NODE_H

#include <vector>
#include <map>
#include <set>


class Graph {
	int key;
	set<int> keys;
	map<pair<int, int>, Trust> edges;
	Graph(vector <Graph*>, int key);
};


#endif //HTN2015_NODE_H
