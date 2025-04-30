#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x1, y_start, x2, y_end;  // Renamed y1 to y_start and y2 to y_end
bool dashedLine = false; // Change to true for dashed line, false for solid

void plot(int x, int y, int count) {
    // For dashed line: only plot if count mod 10 < 5
    if (!dashedLine || (count % 10 < 5)) {
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
    }
}

void bresenham_line() {
    int dx = abs(x2 - x1);
    int dy = abs(y_end - y_start);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y_start < y_end) ? 1 : -1;
    int err = dx - dy;
    int e2;
    int x = x1, y = y_start;
    int count = 0;
    
    while (true) {
        plot(x, y, count);
        count++;
        
        if (x == x2 && y == y_end) break;
        
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
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
    cout << "Enter start point (x1 y_start): ";
    cin >> x1 >> y_start;
    cout << "Enter end point (x2 y_end): ";
    cin >> x2 >> y_end;
    
    cout << "Enter 1 for dashed line, 0 for solid line: ";
    int choice;
    cin >> choice;
    dashedLine = (choice == 1);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Line Algorithm");
    init();
    glutDisplayFunc(bresenham_line);
    glutMainLoop();
    return 0;
}