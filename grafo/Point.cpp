#include "Point.h"

Point::Point(float x_, float y_) {
	x = x_;
	y = y_;
	visited = false;
	added = false;
}

Point::Point() {
	x = 0;
	y = 0;
	visited = false;
	added = false;
}

Point Point::operator =  (const Point& P) {
	this->x = P.x;
	this->y = P.y;
	return *this;
}
bool Point::operator ==  (const Point& P) {
	if (this->x==P.x && this->y == P.y) {
		return true;
	}
	return false;
	
}
Point::~Point() {

}

