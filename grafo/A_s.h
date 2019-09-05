#pragma once
#include "Point.h"
#include <queue>


class A_s {

public:
	A_s();
	~A_s();
	bool Run(Point& P, Point& N);
	
	float euclidean(Point, Point);
	vector<Point*> Path;
	struct compare {
		bool operator()(Point* &P, Point* &Q) {
			return P->cost > Q->cost;
		}
	};
	priority_queue<Point*, vector<Point* >, compare > LESS;
};
