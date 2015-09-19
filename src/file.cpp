#include <vector>
#include <map>

struct Trust{
	int b,d,u;
	Trust(int x, int y, int z) : b(x), d(y), u(z) {};
};

struct Node{
	vector<Node*> neighbours;
	map<Node*, Trust> edge;
	int key;

};

Trust Recomendation(Trust AB, Trust BC){
	return Trust(AB.b*BC.b, AB.b*BC.d, AB.d+AB.u+AB.b*BC.u);
}

Trust Concensus(Trust Ap, Trust Bp){
	return Trust((Ap.b*Bp.u+Bp.b*Ap.u)/(Ap.u+Bp.u-p.u*Bp.u),(Ap.d*Bp.u+Bp.d*Ap.u)/(Ap.u+Bp.u-Ab.u*Bp.u),Ap.u*Bp.u/(Ap.u+Bp.u-Ab.u*Bp.u));
}