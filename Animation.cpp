#include <GL/glut.h>
#include <iostream>
using namespace std;

float x = 100, y = 100;  // Position of object
float dx = 2, dy = 1;    // Speed of movement
float size = 30;         // Size of object
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
        float rad = i * 3.14159 / 180;
        glVertex2f(x + size * cos(rad), y + size * sin(rad));
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
    if (x > windowWidth - size || x < size) dx = -dx;
    if (y > windowHeight - size || y < size) dy = -dy;
    
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
    cin >> size;
    
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