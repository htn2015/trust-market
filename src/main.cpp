#include <iostream>
#include <sstream>
#include <functional>
#include "headers/Graph.h"

#include "headers/Database.h"
using namespace std;

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	for(int i=0; i<argc; ++i) {
		cout << azColName[i] << " : " << argv[i] << endl;
	}
	return 0;
}

int main() {

	Database db;
	db << "drop table user; create table if not exists user ("
	"   _id integer primary key autoincrement not null,"
	" name varchar(256), weight integer"
	");";

	for(int i = 0; i < 200; ++i)
		db << "insert into user values('" << i << "', 'naaame', '" << i << "');";

	db.execute("select * from user", callback);

    //Client client;
    /*
	vector<Graph*> gr;
	map<int, Trust> tr;
	Graph* C = new Graph(gr, tr, 12);
	gr.push_back(C);
	tr.insert(make_pair(12, Trust(0.2,0.6,0.1)));
	Graph* A = new Graph(gr, tr, 2);
	Graph* B = new Graph(gr, tr, 3);
	vector<Graph*> g;
	g.push_back(A);
	g.push_back(B);
	map<int, Trust> t;
	t.insert(make_pair(2, Trust(0.9,0,0.1)));
	t.insert(make_pair(3, Trust(0.8,0,0.2)));
	Graph* D = new Graph(g,t,1);
	cout << D->edges.find(make_pair(2,12))->second.b << endl; */

}