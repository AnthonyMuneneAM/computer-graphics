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
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // Set the viewing area
}

// Function to draw an ellipse using Bresenham's ellipse drawing algorithm
void drawEllipse(int centerX, int centerY, int radiusX, int radiusY)
{
    glColor3f(0.0, 1.0, 0.0); // Set color to green

    int x = 0;
    int y = radiusY;
    int decision = 2 * pow(radiusY, 2) - pow(radiusX, 2) * radiusY + pow(radiusX, 2) / 4;

    glBegin(GL_POINTS);

    // Region 1
    while (2 * pow(radiusY, 2) * x <= 2 * pow(radiusX, 2) * y)
    {
        glVertex2i(centerX + x, centerY + y); // Draw a point at (centerX + x, centerY + y)
        glVertex2i(centerX - x, centerY + y); // Draw a point at (centerX - x, centerY + y)
        glVertex2i(centerX - x, centerY - y); // Draw a point at (centerX - x, centerY - y)
        glVertex2i(centerX + x, centerY - y); // Draw a point at (centerX + x, centerY - y)

        x++;

        if (decision < 0)
        {
            decision += 2 * pow(radiusY, 2) * x + pow(radiusY, 2);
        }
        else
        {
            y--;
            decision += 2 * pow(radiusY, 2) * x - 2 * pow(radiusX, 2) * y + pow(radiusY, 2);
        }
    }

    // Region 2
    decision = 2 * pow(radiusY, 2) * (x + 0.5) * (x + 0.5) + 2 * pow(radiusX, 2) * (y - 1) * (y - 1) - pow(radiusX, 2) * pow(radiusY, 2);

    while (y >= 0)
    {
        glVertex2i(centerX + x, centerY + y); // Draw a point at (centerX + x, centerY + y)
        glVertex2i(centerX - x, centerY + y); // Draw a point at (centerX - x, centerY + y)
        glVertex2i(centerX - x, centerY - y); // Draw a point at (centerX - x, centerY - y)
        glVertex2i(centerX + x, centerY - y); // Draw a point at (centerX + x, centerY - y)

        y--;

        if (decision > 0)
        {
            decision += pow(radiusX, 2) - 2 * pow(radiusX, 2) * y;
        }
        else
        {
            x++;
            decision += 2 * pow(radiusY, 2) * x - 2 * pow(radiusX, 2) * y + pow(radiusX, 2);
        }
    }

    glEnd();
    glFlush();
}

// Function to display the ellipse in the window
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawEllipse(0, 0, 6, 4); // Draw an ellipse centered at (0, 0) with radiusX = 6 and radiusY = 4

    glFlush();
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ellipse Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
