#include "Node.h"

Graph::Graph(vector<Graph*> thought, int key) : key(key) {
	for(vector<Graph*>::iterator i; i<thought.end(); i++){
		keys.insert(i->keys.begin(), i->keys.end());
	}
}