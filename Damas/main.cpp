#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "include/Fichas.h"
#include "MinMax.h"
#define KEY_ESC 27
#define KEY_NEXT 9

using namespace std;

Minmax* mym;
bool jugador =true;
vector<Fichas *> _fichas;
board tablero(8);

void cargarFichas()
{
    _fichas.clear();
    bool color =0;
    int contador=0;
    int _i,_j;
    for(int i =0;i<8;++i)
    {
        for(int j =0;j<8;++j)
        {
            if(tablero[i][j]=='1')
            {
                _fichas.push_back(new Fichas(j,i,0));

            }
            else if(tablero[i][j]=='2')
            {
                _fichas.push_back(new Fichas(j,i,1));
            }

        }
    }
}

void dibujarFicha()
{
    for(int i=0;i<_fichas.size();++i)
    {
        glPushMatrix();
            glPointSize(30.0f);
            if(_fichas[i]->color)
            {
                glColor3f(0.0f,0.0f,1.0f);
            }
            else
            {
                glColor3f(1.0f,0.0f,0.0f);
            }
            glBegin(GL_POINTS);
                glVertex2i(((_fichas[i]->posx)*75) -300+37,((_fichas[i]->posy)*75)-300+37);
            glEnd();
        glPopMatrix();
    }
}

int l =75;
void _tablero()
{
    int x =-300,y=300,x1=300,y1=-300;
    for(int f=0;f<8;++f)
    {
        for(int c=0;c<8;++c)
        {
            if((f+c+1)%2==0)
            {
                glColor3f(0.0f,0.0f,0.0f);
                glBegin(GL_QUADS);
                    glVertex2i(x,y);
                    glVertex2i(x,y-l);
                    glVertex2i(x+l,y-l);
                    glVertex2i(x+l,y);
                glEnd();

            }
            else
            {
                glColor3f(255.0f,255.0f,255.0f);
                glBegin(GL_QUADS);
                    glVertex2i(x,y);
                    glVertex2i(x,y-l);
                    glVertex2i(x+l,y-l);
                    glVertex2i(x+l,y);
                glEnd();
            }
            x+=l;
        }
        y-=l;
        x=-300;
    }
}

void glPaint(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();
	glPushMatrix();
        glColor3f(0.7f,0.35f,0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
            glVertex2i(-300,300);glVertex2i(-300,-300);
            glVertex2i(-300,-300);glVertex2i(300,-300);
            glVertex2i(300,-300);glVertex2i(300,300);
            glVertex2i(300,300);glVertex2i(-300,300);
        glEnd();
	glPopMatrix();
	_tablero();
	dibujarFicha();
	glutSwapBuffers();
	glutPostRedisplay();
}

void mostrarTab()
{
    for(int i =0;i<tablero.size();++i)
    {
        cout<< "|";
        for(int j=0;j<tablero[i].size();++j)
        {
            cout<<tablero[7-i][j]<<"|";
        }
        cout<<endl;
    }
    cout<<endl;
}

void parametrizacion(int &x,int &y)
{
    if(x >= 400)
    {
        x = x - 400;
    }
    else
    {
        x = (400-x)*(-1);
    }
    if(y <= 400)
    {
        y = 400 - y;
    }
    else
    {
        y = (y-400)*(-1);
    }
}

float dEuclidiana(int x,int y,int a,int b)
{
    return sqrt(pow((x-a),2) + pow((y-b),2));
}

int buscar(int x, int y)
{
    int cx;
    int cy;
    for(int i = 0; i < _fichas.size(); ++i)
    {
        int cx = _fichas[i]->posx*75 -300+37;
        int cy = _fichas[i]->posy*75 -300+37;
        if(dEuclidiana(x,y, cx, cy) < 37.5)
        {
            return i;
        }
    }
    return -1;
}

void comer(int cx,int cy,int& x,int& y)
{
    int mx = (cx+x)/2,my = (cy+y)/2;
    cout<<"comer: "<<mx<<"-"<<my<<endl;
    if(tablero[my][mx]=='2')
    {
        tablero[my][mx] = '0';
        tablero[cy][cx] = '0';
        tablero[y][x] = '1';
    }
    mostrarTab();
}
int ficha_seleccionada = -1;
void OnMouseClick(int button, int state, int x, int y)
{
    parametrizacion(x, y);
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        int posicion  = buscar(x,y);
        if(posicion != -1){
            ficha_seleccionada = posicion;
        }
        cout<<posicion<<"<-< pos"<<endl;
    }
//    printTab();
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        int posicion  = buscar(x,y);
        if(ficha_seleccionada != -1){
            if(posicion == -1){
                x += 300; x /= 75;
                y += 300; y /= 75;
                int cx = _fichas[ficha_seleccionada]->posx;
                int cy = _fichas[ficha_seleccionada]->posy;
                cout<<x<<","<<y<<" | "<<cx<<","<<cy<<endl;
                if(x != cx && y != cy && y-1 == cy && (x-1==cx || x+1 == cx)){
                    tablero[cy][cx] = '0';
                    tablero[y][x] = '1';
                    _fichas[ficha_seleccionada]->posx = x;
                    _fichas[ficha_seleccionada]->posy = y;
                }
                if(x != cx && y != cy && y-2 == cy && (x-2==cx || x+2 == cx)){
                    comer(cx,cy,x,y);
                    _fichas[ficha_seleccionada]->posx = x;
                    _fichas[ficha_seleccionada]->posy = y;
                }
            }
        }
    }
    cargarFichas();
}


void init_GL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
    glOrtho(-400.0f, 400.0f, -400.0f, 400.0f, -1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
GLvoid window_redraw(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	default:{
        mym = new Minmax(tablero,0,5,1);
        tablero = mym->elegir();
        mostrarTab();
        cargarFichas();
		break;
		}
	}
}

////////////////////////

int main(int argc, char** argv)
{
    for(int i=0;i<8;++i){
        tablero[i].assign(8,'0');
    }
    for(int i=0; i<8; ++i){
        for(int j=0; j<3; ++j){
            if((i+j)%2){
                tablero[j][i]='1';
            }
        }
    }
    for(int i=0; i<8; ++i){
        for(int j=5; j<8; ++j){
            if((i+j)%2){
                tablero[j][i]='2';
            }
        }
    }
    for(size_t i=0;i<tablero.size();++i){
        cout<<"|";
        for(size_t j=0;j<tablero[i].size();++j){
            cout<<tablero[7-i][j]<<"|";
        }
        cout<<endl;
    }
    cargarFichas();
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(10, 10); //posicion de la ventana
	glutCreateWindow("DAMAS"); //titulo de la ventana

   // mym = new MinMax(elTablero,0,4,1);

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);

	glutMainLoop(); //bucle de rendering
}






