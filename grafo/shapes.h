#pragma once
#include <GL/glut.h>
#include "Point.h"
class shapes{
public:
	shapes();
	~shapes();
	void points_(Point);
	void lines_(Point,Point);
};

