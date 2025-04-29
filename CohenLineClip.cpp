#include <GL/glut.h>
#include <iostream>
using namespace std;

int xmin = 100, ymin = 100, xmax = 400, ymax = 300;
int x1, y1, x2, y2;
bool lineDrawn = false;

// Region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

int getCode(int x, int y) {
    int code = INSIDE;
    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

void cohenSutherland() {
    int code1 = getCode(x1, y1);
    int code2 = getCode(x2, y2);
    bool accept = false;
    
    while (true) {
        if (!(code1 | code2)) { // Both inside
            accept = true;
            break;
        } else if (code1 & code2) { // Both outside same region
            break;
        } else {
            int code = code1 ? code1 : code2;
            int x, y;
            
            if (code & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (code & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (code & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (code & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }
            
            if (code == code1) {
                x1 = x; y1 = y;
                code1 = getCode(x1, y1);
            } else {
                x2 = x; y2 = y;
                code2 = getCode(x2, y2);
            }
        }
    }
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw window
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
    
    // Draw original line in blue
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
    
    // Draw clipped line in red
    if (accept) {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
    
    glFlush();
}

void display() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw window
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
    
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    y = 480 - y; // Invert y coordinate
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!lineDrawn) {
            x1 = x; y1 = y;
            lineDrawn = true;
        } else {
            x2 = x; y2 = y;
            lineDrawn = false;
            cohenSutherland();
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        if (lineDrawn) {
            lineDrawn = false;
            glClear(GL_COLOR_BUFFER_BIT);
            display();
        }
    } else if (key == 27) { // ESC
        exit(0);
    }
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}