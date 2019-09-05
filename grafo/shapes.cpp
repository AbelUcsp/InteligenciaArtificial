#include "shapes.h"
shapes::shapes() {

}
void shapes::points_(Point p) {
	glBegin(GL_POINTS);	
	glColor3d(255, 0, 0);
	glVertex2d(p.x, p.y);
	glEnd();
}

void shapes::lines_(Point p, Point q) {	
	glBegin(GL_LINES);
		glLineWidth(0.5f);
		glColor3d(0, 255, 255);
		glVertex2f(p.x, p.y);
		glVertex2f(q.x, q.y);
	glEnd();
}
shapes::~shapes() {

}