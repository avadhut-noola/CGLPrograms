#include <GL/glut.h>
#include <iostream>
using namespace std;

int radius, centerX = 0, centerY = 0;

void plotPoints(int x, int y) {
    // Plot points in all 8 octants
    glBegin(GL_POINTS);
    glVertex2i(centerX + x, centerY + y);
    glVertex2i(centerX + y, centerY + x);
    glVertex2i(centerX + y, centerY - x);
    glVertex2i(centerX + x, centerY - y);
    glVertex2i(centerX - x, centerY - y);
    glVertex2i(centerX - y, centerY - x);
    glVertex2i(centerX - y, centerY + x);
    glVertex2i(centerX - x, centerY + y);
    glEnd();
    glFlush();
}

void bresenhamCircle() {
    int x = 0, y = radius;
    int d = 3 - 2 * radius;
    
    plotPoints(x, y);
    
    while (x < y) {
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
        plotPoints(x, y);
    }
}

void init() {
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    gluOrtho2D(-320, 320, -240, 240);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw coordinate axes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(320, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 240);
    glEnd();
    
    glColor3f(1, 0, 0); // Reset to red for circle
}

int main(int argc, char **argv) {
    cout << "Enter circle radius: ";
    cin >> radius;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Circle");
    init();
    glutDisplayFunc(bresenhamCircle);
    glutMainLoop();
    return 0;
}