#include "Graph.h"
#include "Trust.h"

/*
Graph::Graph(vector<Graph*> thought, map<int, Trust> weights, int key) : key(key) {
	for(vector<Graph*>::iterator i = thought.end(); i<thought.end(); i++){
		keys.insert(i->keys.begin(), i->keys.end());
	}

	for(set<int>::iterator i = keys.begin(); i<keys.end(); i++){
		for(set<int>::iterator j = keys.begin(); j<keys.end(); j++){
			Trust value(0,0,1);
			for(vector<Graph*>::iterator p = thought.end(); p<thought.end(); p++){
				map<pair<int, int>, Trust>::iterator z = p->edges.find(i->key, j->key);
				if(z != p->edges.end())
					value = consensus(value, recommendation(*weights.find(thought->key),*z));
			}
		}
	}
}
*/