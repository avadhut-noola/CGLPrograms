#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Global variables
vector<pair<float, float>> originalPoints;
vector<pair<float, float>> transformedPoints;
int choice = 0;

// For transformations
float sx, sy;              // Scaling factors
float angle;               // Rotation angle in degrees
float cx, cy;              // Rotation center point
int reflectionAxis;        // 1=x-axis, 2=y-axis, 3=origin

void drawAxes() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    // X-axis
    glVertex2f(-300, 0);
    glVertex2f(300, 0);
    // Y-axis
    glVertex2f(0, -300);
    glVertex2f(0, 300);
    glEnd();
}

void drawObject(vector<pair<float, float>>& points, float r, float g, float b) {
    if (points.size() < 3) return;
    
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (auto& p : points) {
        glVertex2f(p.first, p.second);
    }
    glEnd();
}

void performScaling() {
    transformedPoints.clear();
    for (auto& p : originalPoints) {
        transformedPoints.push_back({p.first * sx, p.second * sy});
    }
}

void performRotation() {
    float rad = angle * M_PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);
    
    transformedPoints.clear();
    for (auto& p : originalPoints) {
        // Translate to origin
        float x = p.first - cx;
        float y = p.second - cy;
        
        // Rotate
        float xNew = x * cosA - y * sinA;
        float yNew = x * sinA + y * cosA;
        
        // Translate back
        transformedPoints.push_back({xNew + cx, yNew + cy});
    }
}

void performReflection() {
    transformedPoints.clear();
    for (auto& p : originalPoints) {
        if (reflectionAxis == 1) {  // About X-axis
            transformedPoints.push_back({p.first, -p.second});
        } else if (reflectionAxis == 2) {  // About Y-axis
            transformedPoints.push_back({-p.first, p.second});
        } else if (reflectionAxis == 3) {  // About Origin
            transformedPoints.push_back({-p.first, -p.second});
        }
    }
}   

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawAxes();
    drawObject(originalPoints, 0.0, 0.0, 1.0);  // Original in blue
    
    if (choice != 0) {
        drawObject(transformedPoints, 1.0, 0.0, 0.0);  // Transformed in red
    
        // Display transformation parameters
        if (choice == 1) {
            cout << "Scaling: sx=" << sx << ", sy=" << sy << endl;
        } else if (choice == 2) {
            cout << "Rotation: angle=" << angle << " degrees, center=(" << cx << "," << cy << ")" << endl;
        } else if (choice == 3) {
            cout << "Reflection: ";
            if (reflectionAxis == 1) cout << "about x-axis" << endl;
            else if (reflectionAxis == 2) cout << "about y-axis" << endl;
            else if (reflectionAxis == 3) cout << "about origin" << endl;
        }
    }
    
    glFlush();
}

void applyTransformation() {
    switch (choice) {
        case 1: performScaling(); break;
        case 2: performRotation(); break;
        case 3: performReflection(); break;
        default: break;
    }
    glutPostRedisplay();
}

void mainMenu(int option) {
    if (option == 0) exit(0);
    choice = option;
    
    if (choice == 1) {
        cout << "Enter scaling factors (sx sy): ";
        cin >> sx >> sy;
    } else if (choice == 2) {
        cout << "Enter rotation angle (degrees): ";
        cin >> angle;
        cout << "Enter rotation center (cx cy): ";
        cin >> cx >> cy;
    } else if (choice == 3) {
        cout << "Enter reflection axis (1=x-axis, 2=y-axis, 3=origin): ";
        cin >> reflectionAxis;
    }
    
    applyTransformation();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char** argv) {
    // Default triangle
    originalPoints = {{0, 0}, {100, 0}, {50, 100}};
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("2D Transformations");
    
    init();
    glutDisplayFunc(display);
    
    // Create menu
    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Scaling", 1);
    glutAddMenuEntry("Rotation", 2);
    glutAddMenuEntry("Reflection", 3);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    return 0;
}