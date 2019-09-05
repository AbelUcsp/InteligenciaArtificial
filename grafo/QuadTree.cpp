#include "QuadTree.h"

QuadTree::QuadTree() {


}
QuadTree::QuadTree(float size, float div) {
	
	float step = size / div;
	add_points(step, size);
	add_edges();

}
bool QuadTree::SearchPoint(Point P, Point*& Q) {
	for (unsigned int i = 0; i  < Matrix.size(); i++) {
		for (unsigned int j = 0; j < Matrix.size(); j++) {
			if (Matrix[i][j] == P) {
				Q = &Matrix[i][j];
				return 1;
			}
		}
	}
	return 0;
}
bool QuadTree::SearchEdge(Point * P, Point* Q, int &pos1, int& pos2) {
	bool state = false;
	for (unsigned int i = 0; i < P->Edges.size(); i++) {
		if (P->Edges[i]->VertexB == Q) {
			pos1 = i;
			state = true;
			break;
		}
	}
	for (unsigned int i = 0; i < Q->Edges.size(); i++) {
		if (Q->Edges[i]->VertexB == P) {
			pos2 = i;
			break;
		}
	}
	return (state) ? true : false;
}
bool QuadTree::GetQuads(Point P, Point Q, int &x_1, int &x_2, int &y_1, int&y_2) {
	for (unsigned int i = 0; i < Matrix.size();i++) {
		if (Matrix[0][i].x >= P.x){x_1 = i;break;}
	}
	for (unsigned int i = 0; i < Matrix.size(); i++) {
		if (Q.x <= Matrix[0][i].x){x_2 = i;break;}
	}
	for (unsigned int i = 0; i < Matrix.size(); i++) {
		if (Matrix[i][0].y >= P.y) {y_1 = i;break;}
	}
	for (unsigned int i = 0; i < Matrix.size(); i++) {
		if (Q.y <= Matrix[i][0].y) {y_2 = i-1;break;}
	}
	return true;
}
bool QuadTree::DeleteEdge(Point P,Point Q) {

	int x_1, x_2, y_1, y_2;
	int pos1, pos2;

	GetQuads(P,Q, x_1, x_2, y_1, y_2);

	for ( int i = y_2; i < y_1; i++) {
		for ( int j = x_1;j < x_2; j++) {
			if(SearchEdge(&Matrix[i][j], &Matrix[i][j+1],pos1,pos2)){
				Matrix[i][j].Edges.erase(Matrix[i][j].Edges.begin() + pos1);
				Matrix[i][j + 1].Edges.erase(Matrix[i][j + 1].Edges.begin() + pos2);
			}
			if (SearchEdge(&Matrix[i][j], &Matrix[i + 1][j + 1], pos1, pos2)) {
				Matrix[i][j].Edges.erase(Matrix[i][j].Edges.begin() + pos1);
				Matrix[i + 1][j + 1].Edges.erase(Matrix[i + 1][j + 1].Edges.begin() + pos2);
			}
			if (SearchEdge(&Matrix[i][j], &Matrix[i + 1][j], pos1, pos2)) {
				Matrix[i][j].Edges.erase(Matrix[i][j].Edges.begin() + pos1);
				Matrix[i + 1][j].Edges.erase(Matrix[i + 1][j].Edges.begin() + pos2);
			}													
	    }
	}
	return 0;
}
void QuadTree::add_points(float step,float size) {

	for (unsigned int i = 0; i * step < size; i++) {
		vector<Point>Rows;
		for (unsigned int j = 0; j * step < size; j++) {
			Rows.push_back(Point(step * j, step * i));
		}
		Matrix.push_back(Rows);
	}
}
void QuadTree::add_edges() {

	for (unsigned int i = 0; i < Matrix.size()-1; i++) {
		for (unsigned int j = 0; j < Matrix.size()-1; j++) {

				Edge* nuevo = new Edge(&Matrix[i][j],&Matrix[i][j + 1]);
				Matrix[i][j].Edges.push_back(nuevo);
				Edge* nuevo2 = new Edge(&Matrix[i][j + 1], &Matrix[i][j]);
				Matrix[i][j + 1].Edges.push_back(nuevo2);

				Edge* nuevo3 = new Edge(&Matrix[i][j], &Matrix[i + 1][j + 1]);
				Matrix[i][j].Edges.push_back(nuevo3);
				Edge* nuevo4 = new Edge(&Matrix[i + 1][j + 1], &Matrix[i][j]);
				Matrix[i + 1][j + 1].Edges.push_back(nuevo4);

				Edge* nuevo5 = new Edge(&Matrix[i][j], &Matrix[i + 1][j]);
				Matrix[i][j].Edges.push_back(nuevo5);
				Edge* nuevo6 = new Edge(&Matrix[i + 1][j], &Matrix[i][j]);
				Matrix[i + 1][j].Edges.push_back(nuevo6);
		}	
	}

}
void QuadTree::print_vertex() {
	for (unsigned int i = 0; i < Matrix.size();i++) {
		for (unsigned int j = 0; j < Matrix.size(); j++) {
			shape.points_(Matrix[i][j]);
		}
	}
}
void QuadTree::print_edges() {
	for (unsigned int i = 0; i < Matrix.size() - 1; i++) {
		for (unsigned int j = 0; j < Matrix.size() - 1; j++) {
			shape.lines_(Matrix[i][j], Matrix[i][j + 1]);
			shape.lines_(Matrix[i][j], Matrix[i + 1][j + 1]);
			shape.lines_(Matrix[i][j], Matrix[i + 1][j]);
		}
	}
}
QuadTree::~QuadTree() {


}
