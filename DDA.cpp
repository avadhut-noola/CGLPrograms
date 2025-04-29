#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float x1, y1, x2, y2;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void DDA_line() {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    float xInc = dx / steps;
    float yInc = dy / steps;
    
    float x = x1, y = y1;
    
    for (int i = 0; i <= steps; i++) {
        plot(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

void init() {
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    gluOrtho2D(-320, 320, -240, 240); // Divide screen into 4 quadrants
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw coordinate axes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(320, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 240);
    glEnd();
    
    glColor3f(1, 0, 0); // Reset color to red for line
}

int main(int argc, char **argv) {
    cout << "Enter start point (x1 y1): ";
    cin >> x1 >> y1;
    cout << "Enter end point (x2 y2): ";
    cin >> x2 >> y2;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line Algorithm");
    init();
    glutDisplayFunc(DDA_line);
    glutMainLoop();
    return 0;
}