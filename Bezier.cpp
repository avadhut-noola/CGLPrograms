#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

struct Point { double x, y; };
vector<Point> ctrlPoints;
int it, numCtrlPoints;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

double factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

double binomial(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

Point bezierPoint(vector<Point>& points, double t) {
    Point p = {0, 0};
    int n = points.size() - 1;
    
    for (int i = 0; i <= n; i++) {
        double blend = binomial(n, i) * pow(t, i) * pow(1 - t, n - i);
        p.x += points[i].x * blend;
        p.y += points[i].y * blend;
    }
    
    return p;
}

void drawBezier(vector<Point>& points) {
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    
    for (double t = 0; t <= 1.0; t += 0.01) {
        Point p = bezierPoint(points, t);
        glVertex2d(p.x, p.y);
    }
    
    glEnd();
    glFlush();
}

void bezierFractal(vector<Point>& points, int depth) {
    if (depth == 0) {
        drawBezier(points);
        return;
    }
    
    // Create sub-curves for the fractal pattern
    vector<Point> left(points.size()), right(points.size());
    
    // Left subcurve (first half)
    for (int i = 0; i < points.size(); i++) {
        double t = 0.33; // Scale factor
        left[i].x = points[i].x * (1-t) + points[0].x * t;
        left[i].y = points[i].y * (1-t) + points[0].y * t;
    }
    
    // Right subcurve (second half)
    for (int i = 0; i < points.size(); i++) {
        double t = 0.33; // Scale factor
        right[i].x = points[i].x * (1-t) + points[points.size()-1].x * t;
        right[i].y = points[i].y * (1-t) + points[points.size()-1].y * t;
    }
    
    bezierFractal(left, depth - 1);
    bezierFractal(right, depth - 1);
}

void display() {
    bezierFractal(ctrlPoints, it);
}

int main(int argc, char** argv) {
    cout << "Enter number of control points: ";
    cin >> numCtrlPoints;
    
    ctrlPoints.resize(numCtrlPoints);
    for (int i = 0; i < numCtrlPoints; i++) {
        cout << "Enter control point " << i+1 << " (x y): ";
        cin >> ctrlPoints[i].x >> ctrlPoints[i].y;
    }
    
    cout << "No. of iterations: ";
    cin >> it;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Bezier Curve Fractal");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}