#include <GL/glut.h>
#include <cmath>

// Anthony Munene Mwangi
// SCT212-0050/2018

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Define the two endpoints
    float x1 = -2.0, y1 = 2.0;
    float x2 = 3.0, y2 = 7.0;

    // Calculate dx and dy
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Calculate the slope
    float slope = dy / dx;

    // Check if the slope is greater than 1 or less than -1
    bool steep = (fabs(slope) > 1.0);

    // If the slope is steep, swap x and y coordinates
    if (steep)
    {
        float temp = x1;
        x1 = y1;
        y1 = temp;
        temp = x2;
        x2 = y2;
        y2 = temp;
    }

    // Swap the endpoints if x1 is greater than x2
    if (x1 > x2)
    {
        float temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    // Recalculate dx and dy after potential swaps
    dx = x2 - x1;
    dy = y2 - y1;

    // Calculate the error factor
    float error = dx / 2.0;
    int ystep = (y1 < y2) ? 1 : -1;
    int y = static_cast<int>(y1);

    // Loop through each x coordinate
    for (int x = static_cast<int>(x1); x <= static_cast<int>(x2); x++)
    {
        // Set the pixel color with anti-aliasing
        if (steep)
        {
            glColor3f(1.0, 0.0, 0.0); // Red color
            glBegin(GL_POINTS);
            glVertex2f(static_cast<float>(y), static_cast<float>(x));
            glEnd();
            glColor3f(0.0, 0.0, 1.0); // Blue color
            glBegin(GL_POINTS);
            glVertex2f(static_cast<float>(y) + 1.0, static_cast<float>(x));
            glEnd();
        }
        else
        {
            glColor3f(1.0, 0.0, 0.0); // Red color
            glBegin(GL_POINTS);
            glVertex2f(static_cast<float>(x), static_cast<float>(y));
            glEnd();
            glColor3f(0.0, 0.0, 1.0); // Blue color
            glBegin(GL_POINTS);
            glVertex2f(static_cast<float>(x), static_cast<float>(y) + 1.0);
            glEnd();
        }

        // Update the error factor and y coordinate
        error -= fabs(slope);
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Xiaolin Line One");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
