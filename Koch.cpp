#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

double x, y, len, angle;
int it;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

void line(double x1, double y1, double x2, double y2) {
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
    glFlush();
}

void koch(double x, double y, double len, double angle, int it) {
    if (it == 0) {
        double nx = x + len * cos(angle * M_PI / 180);
        double ny = y + len * sin(angle * M_PI / 180);
        line(x, y, nx, ny);
        return;
    }
    
    len /= 3;
    koch(x, y, len, angle, it - 1);
    
    x += len * cos(angle * M_PI / 180);
    y += len * sin(angle * M_PI / 180);
    koch(x, y, len, angle + 60, it - 1);
    
    x += len * cos((angle + 60) * M_PI / 180);
    y += len * sin((angle + 60) * M_PI / 180);
    koch(x, y, len, angle - 60, it - 1);
    
    x += len * cos((angle - 60) * M_PI / 180);
    y += len * sin((angle - 60) * M_PI / 180);
    koch(x, y, len, angle, it - 1);
}

void display() {
    koch(x, y, len, angle, it);
}

int main(int argc, char** argv) {
    cout << "Enter Starting Point x y: ";
    cin >> x >> y;
    cout << "Length and angle of line: ";
    cin >> len >> angle;
    cout << "No. of iterations: ";
    cin >> it;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Koch Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}