#include <GL/glut.h>
#include <cmath>

// Anthony Munene Mwangi
// SCT212-0050/2018

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    int x1 = 0, y1 = 3;
    int x2 = 6, y2 = 5;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        glColor3f(1.0, 0.0, 0.0); // Red color
        glBegin(GL_POINTS);
        glVertex2i(x1, y1);
        glEnd();

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Bresenham's Line Two");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
