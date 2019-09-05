#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "time.h"
#include <fstream>
#include <string>
#include "QuadTree.h"
#include "BusquedaCiegaP.h"
#include "A_s.h"

#define KEY_ENTER 13
#define KEY_UP  119
#define KEY_DOWN 115
#define KEY_LEFT 97 
#define KEY_RIGHT 100
using namespace std;

int mx = 0;
int my = 0;

int fx = 0;
int fy = 0;
struct PosPoint{
	float x = 0;
	float y = 0;
};


bool r = false;
QuadTree Quad(500, 40);
PosPoint A, B;
PosPoint ArrayP[2]={A,B};
int Pos = 0;

BusquedaCiegaP IA;
float Step = 12.5;
A_s IA2;
vector<float>Quads;
vector<float>Region;
bool RunState = false;
Point* P;
Point* Q;

void OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		mx = x;
		my = 500-y;
		cout << "init Pos:" << mx << "-" << my << endl;
		Quads.push_back(mx);
		Quads.push_back(my);
		
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		fx = x;
		fy = 500-y;
		cout << "fin Pos:" << fx << "-" << fy << endl;
		Quads.push_back(fx);
		Quads.push_back(fy);
		Quad.DeleteEdge(Point(Quads[Quads.size() - 4], Quads[Quads.size() - 3]), Point(Quads[Quads.size() - 2], Quads[Quads.size()-1]));
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		RunState = true;	
		Quad.SearchPoint(Point(ArrayP[0].x, ArrayP[0].y), P);
		Quad.SearchPoint(Point(ArrayP[1].x, ArrayP[1].y), Q);
		IA2.Run(*P, *Q);
	}

}

//dibuja un simple gizmo
void displayGraph() {
	Quad.print_vertex();
	glBegin(GL_POINTS);
		glColor3d(0, 255, 0);
		glVertex2d(ArrayP[0].x, ArrayP[0].y);
	glEnd();
	glBegin(GL_POINTS);
		glColor3d(0, 0, 255);
		glVertex2d(ArrayP[1].x, ArrayP[1].y);
	glEnd();
	//Quad.print_edges();	
	for (unsigned int i = 0; Quads.size()%4==0 && i < Quads.size();i+=4) {
		glBegin(GL_QUADS);
		    glColor3d(0, 0, 255);
			glVertex2f(Quads[i], Quads[i+1]);
			glVertex2f(Quads[i + 2], Quads[i + 1]);
			glVertex2f(Quads[i + 2], Quads[i + 3]);
			glVertex2f(Quads[i], Quads[i + 3]);			
		glEnd();
	}
	if (RunState) {
		//cout << "Apretato" << endl;
		
		for (unsigned int i = 0; i < (IA2.Path.size()-1); i++) {
			glBegin(GL_LINES);
				glColor3d(0, 0, 255);
				glVertex2f(IA2.Path[i]->x, IA2.Path[i]->y);
				glVertex2f(IA2.Path[i + 1]->x, IA2.Path[i + 1]->y);
			glEnd();
		}
		
	}

	//if(Quads.size()==4){
	//	Region
	//}
}
void idle() { // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}
//funcion llamada a cada imagen
void display(void) {
	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();
	glOrtho(0, 500, 0, 500, -1.0f, 1.0f);
	displayGraph();
	glutSwapBuffers();
	
}
void init(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
		//modo projeccion 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
		case KEY_ENTER: {
			Pos++;
			if (Pos==2) {
				Pos = 0;
			}
			break;
		}		
		case KEY_UP: {
			ArrayP[Pos].y += Step;
			break;
		}				
		case KEY_DOWN: {
			ArrayP[Pos].y -= Step;
			break;
		}				
		case KEY_LEFT: {
			ArrayP[Pos].x -= Step;
			break;
		}					
		case KEY_RIGHT: {
			ArrayP[Pos].x += Step;
			break;
		}				
		default:
			break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("IA LAb 1"); //titulo de la ventana
	init(); //funcion de inicializacion de OpenGL



	//Quad.DeleteEdge(Point(50,300), Point(300, 50));
	//IA2.Run(*P, *Q);
	
	glutDisplayFunc(display);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutMouseFunc(&OnMouseClick);
	glutKeyboardFunc(&window_key);

	glutIdleFunc(&idle);
	glutMainLoop(); //bucle de rendering
	return 0;
}