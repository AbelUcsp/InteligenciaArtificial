#include "A_s.h"
A_s::A_s(){

}

A_s::~A_s(){

}
float A_s::euclidean(Point P, Point N) {
	return sqrt(pow(abs(N.x - P.x), 2) + pow(abs(N.y - P.y), 2) );
}
bool A_s::Run(Point& P, Point& N) {
	float G;
	float H;
	Point* V;
	//P.visited = true;
	LESS.push(&P);
	while (!LESS.empty()) {
		V = LESS.top();
		V->visited = true;
		Path.push_back(V);
		LESS = priority_queue<Point*, vector<Point* >, compare>();
		if (*V == N) {
			return true;
		}else{
			for (unsigned int i = 0; i < V->Edges.size(); i++) {
				if (V->Edges[i]->VertexB->visited == false) {
					G = euclidean(*V->Edges[i]->VertexA, *V->Edges[i]->VertexB);
					H = euclidean(*V->Edges[i]->VertexB, N);
					V->Edges[i]->VertexB->cost = G + H;
					//V->Edges[i]->VertexB->visited = true;
					LESS.push(V->Edges[i]->VertexB);
				}
			}			
		}
	}
	return false;
}