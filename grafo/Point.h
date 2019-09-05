#pragma once
#include "Edge.h"
#include <vector>
using namespace std;
class Edge;
class Point {
public:

	Point();
	Point(float, float);
	//vector<int>sdsd;

	vector<Edge *>Edges;
	float x;
	float y;
	bool visited;
	bool added;
	float cost;
	Point operator = (const Point&);
	bool operator == (const Point&);
	~Point();
	
};
