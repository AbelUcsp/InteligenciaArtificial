#include "BusquedaCiegaP.h"
BusquedaCiegaP::BusquedaCiegaP() {

}
bool BusquedaCiegaP::Run(Point& P, Point& N) {
	L.push(&P);
	Point* V;
	while (!L.empty()) {
		V = L.top();
		V->visited = true;
		Path.push_back(V);
		L.pop();
		if (*V == N) {			
			return true;
		}
		else {
			for (unsigned int i = 0; i < V->Edges.size(); i++) {
				if (V->Edges[i]->VertexB->visited == false && V->Edges[i]->VertexB->added==false) {
					L.push(V->Edges[i]->VertexB);
					V->Edges[i]->VertexB->added = true;
				}
			}

		}
	}
	return false;
}
BusquedaCiegaP::~BusquedaCiegaP() {

}