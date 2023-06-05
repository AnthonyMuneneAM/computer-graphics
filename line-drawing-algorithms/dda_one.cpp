#include <GL/gl.h>
#include <GL/glut.h>

// Anthony Munene Mwangi
// SCT212-0050/2018

// Function to display the scene
void display();

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set up the display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Set the window size
    glutInitWindowSize(800, 600);  // Adjust the window size as needed

    // Create the window
    glutCreateWindow("DDA Line One");

    // Set the clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Set the orthographic viewing area
    gluOrtho2D(-10, 10, -10, 10);

    // Specify the function to call when the window needs to be redrawn
    glutDisplayFunc(display);

    // Enter the event processing loop
    glutMainLoop();
    return 0;
}

void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Define the starting and ending points
    float x0 = -2, y0 = 2; // Starting point coordinates
    float x1 = 3, y1 = 7; // Ending point coordinates

    // Calculate the differences in x and y coordinates
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

    // Loop through each step and plot the pixels
    for (int i = 0; i <= steps; i++) {
        // Set the color to red
        glColor3f(1.0, 0.0, 0.0);

        // Plot the pixel at (x, y)
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();

        // Draw blue hashes (#) around the pixel
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(x + 0.05, y + 0.05);
        glVertex2f(x + 0.05, y - 0.05);
        glVertex2f(x - 0.05, y + 0.05);
        glVertex2f(x - 0.05, y - 0.05);
        glEnd();

        // Update the coordinates for the next step
        x += x_increment;
        y += y_increment;
    }

    // Flush the drawing commands
    glFlush();
}
