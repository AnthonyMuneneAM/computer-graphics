#include <GL/glut.h>
#include <cmath>

// Anthony Munene Mwangi
// SCT212-0050/2018

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Define the starting and ending points
    float x0 = -2, y0 = 2; // Starting point coordinates
    float x1 = 3, y1 = 7; // Ending point coordinates

    // Calculate ΔX and ΔY from the given input
    float dx = x1 - x0;
    float dy = y1 - y0;

    // Determine the number of steps
    float steps = std::max(std::abs(dx), std::abs(dy));

    // Calculate the increments for each step
    float x_increment = dx / steps;
    float y_increment = dy / steps;

    // Set the initial coordinates
    float x = x0;
    float y = y0;

    // Plot the initial point
    glColor3f(0.0, 0.0, 1.0); // Set the color to blue
    glPointSize(5.0); // Set the point size
    glBegin(GL_POINTS);
    glVertex2f(x, y); // Plot the point at (x, y)
    glEnd();

    // Draw the line
    glColor3f(1.0, 0.0, 0.0); // Set the color to red
    glBegin(GL_LINES);
    glVertex2f(x0, y0); // Starting point of the line
    glVertex2f(x1, y1); // Ending point of the line
    glEnd();

    // Loop through each step and plot the points
    for (int i = 0; i < steps; i++)
    {
        // Move along the x-axis
        x += x_increment;
        // Move along the y-axis
        y += y_increment;

        // Draw the blue hashes (#) around the point
        glColor3f(0.0, 0.0, 1.0); // Set the color to blue
        glBegin(GL_LINES);
        glVertex2f(x + 0.05, y + 0.05);
        glVertex2f(x - 0.05, y - 0.05);
        glVertex2f(x + 0.05, y - 0.05);
        glVertex2f(x - 0.05, y + 0.05);
        glEnd();

        // Plot the point
        glColor3f(0.0, 0.0, 1.0); // Set the color to blue
        glPointSize(5.0); // Set the point size
        glBegin(GL_POINTS);
        glVertex2f(x, y); // Plot the point at (x, y)
        glEnd();
    }

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Midpoint Line One");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-10, 10, -10, 10);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
