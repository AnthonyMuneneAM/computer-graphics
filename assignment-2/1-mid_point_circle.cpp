#include <GL/glut.h>
#include <cmath>

// Anthony Munene Mwangi
// SCT212-0050/2018

// Function to initialize OpenGL settings
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set clear color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 10.0, 0.0, 10.0); // Set the viewing area
}

// Function to draw a circle using the midpoint algorithm
void drawCircle(int centerX, int centerY, int radius)
{
    glColor3f(1.0, 0.0, 0.0); // Set color to red

    int x = 0;
    int y = radius;
    int decision = 1 - radius;

    glBegin(GL_POINTS);

    while (y >= x)
    {
        glVertex2i(centerX + x, centerY + y); // Draw a point at (centerX + x, centerY + y)
        glVertex2i(centerX + y, centerY + x); // Draw a point at (centerX + y, centerY + x)
        glVertex2i(centerX - x, centerY + y); // Draw a point at (centerX - x, centerY + y)
        glVertex2i(centerX - y, centerY + x); // Draw a point at (centerX - y, centerY + x)
        glVertex2i(centerX + x, centerY - y); // Draw a point at (centerX + x, centerY - y)
        glVertex2i(centerX + y, centerY - x); // Draw a point at (centerX + y, centerY - x)
        glVertex2i(centerX - x, centerY - y); // Draw a point at (centerX - x, centerY - y)
        glVertex2i(centerX - y, centerY - x); // Draw a point at (centerX - y, centerY - x)

        x++;

        if (decision < 0)
        {
            decision += 2 * x + 1;
        }
        else
        {
            y--;
            decision += 2 * (x - y) + 1;
        }
    }

    glEnd();
    glFlush();
}

// Function to draw a diameter line
void drawDiameter(int centerX, int centerY, int radius)
{
    glColor3f(0.0, 0.0, 0.0); // Set color to black

    glBegin(GL_LINES);
    glVertex2i(centerX - radius, centerY); // Start point of the diameter line
    glVertex2i(centerX + radius, centerY); // End point of the diameter line
    glEnd();
}

// Function to display the circle and diameter in the window
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawCircle(3, 3, 4);    // Draw a circle centered at (3, 3) with a radius of 4 units
    drawDiameter(3, 3, 4);  // Draw a diameter line

    glFlush();
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle and Diameter Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
