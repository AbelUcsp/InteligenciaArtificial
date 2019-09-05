#pragma once
#include <stack>
#include <utility>  
#include "Point.h"
using namespace std;
class BusquedaCiegaP{
public:
	BusquedaCiegaP();
	bool Run(Point& P, Point& N);
	~BusquedaCiegaP();
	stack<Point *>L;
	vector<Point*> Path;
};

