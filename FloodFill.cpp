#include <math.h>
#include <GL/glut.h>
#include<iostream>
using namespace std;
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 480);
}



void floodFill(int x, int y, float* newColor) {
	float color[3];
	 glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
	if(color[0] != newColor[0] || color[1] != newColor[1] || color[2]!= newColor[2])
	{
		glColor3f(newColor[0],newColor[1],newColor[2]);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		glFlush();
		floodFill(x+1, y,newColor);
		floodFill(x, y+1,  newColor);
		floodFill(x-1, y, newColor);
		floodFill(x, y-1, newColor);
	}
	return;
}

void onMouseClick(int button, int state, int x, int y)
{
	float newColor[] = {0, 1, 0};
	cout<<"x is :"<<x<<" y is : "<<y<<endl;
	floodFill(320,230,newColor);
}

void draw_circle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(300,100);
        glVertex2i(300,300);
        glVertex2i(450,100);
	glEnd();
	glFlush();
}

void display(void) {
		draw_circle();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}