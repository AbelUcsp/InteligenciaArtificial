#pragma once

#include "Point.h"
class Point;
class Edge {
public:
	Edge(Point*, Point*);
	Point* VertexA;
	Point* VertexB;
};


