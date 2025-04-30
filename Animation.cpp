#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float x = 100, y = 100;  // Position of object
float dx = 2, dy = 1;    // Speed of movement
float obj_size = 30;     // Size of object (renamed from size to obj_size)
int windowWidth = 640, windowHeight = 480;

void init() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

void drawObject() {
    // Draw a simple circle
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30) {
        float rad = i * M_PI / 180;
        glVertex2f(x + obj_size * std::cos(rad), y + obj_size * std::sin(rad));
    }
    glEnd();
    glFlush();
}

void animate(int value) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Update position with bouncing
    x += dx;
    y += dy;
    
    // Bounce off walls
    if (x > windowWidth - obj_size || x < obj_size) dx = -dx;
    if (y > windowHeight - obj_size || y < obj_size) dy = -dy;
    
    // Draw the object
    drawObject();
    
    // Call animate again after 16ms (about 60fps)
    glutTimerFunc(16, animate, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawObject();
}

int main(int argc, char** argv) {
    cout << "Initial position (x y): ";
    cin >> x >> y;
    cout << "Speed (dx dy): ";
    cin >> dx >> dy;
    cout << "Size: ";
    cin >> obj_size;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Animation");
    
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, animate, 0);
    glutMainLoop();
    
    return 0;
}