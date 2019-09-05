#pragma once
#include "Point.h"
#include <math.h>
#include "shapes.h"
#include "Edge.h"
#include <vector>
#include <math.h>

using namespace std;

class QuadTree{
	public:
		QuadTree();
		QuadTree(float, float);
		~QuadTree();

		void add_points(float,float);
		void add_edges();
		void print_vertex();
		void print_edges();
		float euclidean(Point, Point);
		bool DeleteEdge(Point , Point );
		bool SearchEdge(Point*, Point*, int&, int&);
		bool GetQuads(Point, Point, int& , int& , int& , int&);
		bool SearchPoint(Point,Point*&);
		int MinSize;
		shapes shape;
		vector<vector <Point> >Matrix;
		
};

