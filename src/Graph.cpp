#include "Graph.h"
#include "Trust.h"

using namespace std;

Graph::Graph() { }

/*
Graph::Graph(vector<Graph*>& thought, map<int, Trust>& weights, int key) : key(key) {
	for(vector<Graph*>::iterator i = thought.begin(); i != thought.end(); i++){
		keys.insert((*i)->keys.begin(), (*i)->keys.end());
	}

	keys.insert(key);
	for(set<int>::iterator i = keys.begin(); i != keys.end(); i++){
		for(set<int>::iterator j = keys.begin(); j != keys.end(); j++){
			Trust value(0,0,1);
			if(*i==key){
				map<int, Trust>::iterator r = weights.find(*j);
				if(r!=weights.end()){
					value=r->second;
				}
			}
			for(vector<Graph*>::iterator p = thought.begin(); p != thought.end(); p++){
				map<pair<int, int>, Trust>::iterator z = (*p)->edges.find(make_pair(*i, *j));
				if(z != (*p)->edges.end()){
					value = Trust::consensus(value, Trust::recommendation(weights.find((*p)->key)->second,z->second));
				}
			}
			edges.insert(make_pair(make_pair(*i, *j), value));
		}
	}
}*/



