#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Window dimensions
static int windowWidth = 640;
static int windowHeight = 480;

// Resize function to handle window resizing
static void resize(int width, int height)
{
    // Set the viewport to cover the entire window
    glViewport(0, 0, width, height);

    // Set the projection matrix to an orthographic view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -1, 1);

    // Set the model-view matrix to the identity matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Function to draw a square with given coordinates and color
void drawSquare()
{
    // Set the drawing color to blue
    glColor3d(0, 0, 1);

    // Draw the square
    glBegin(GL_QUADS);
    glVertex2i(-3, 7);
    glVertex2i(6, 7);
    glVertex2i(6, -2);
    glVertex2i(-3, -2);
    glEnd();
}

// Display function to render the scene
static void display(void)
{
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the original square with blue color
    drawSquare();

    // Save the current matrix
    glPushMatrix();

    // Set the drawing color to red
    glColor3d(1, 0, 0);

    // Set the line style to dotted
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);

    // Draw the shadow square in dotted red lines
    glBegin(GL_LINE_LOOP);
    glVertex2i(-3, 7);
    glVertex2i(6, 7);
    glVertex2i(6, -2);
    glVertex2i(-3, -2);
    glEnd();

    // Disable line stippling
    glDisable(GL_LINE_STIPPLE);

    // Restore the saved matrix
    glPopMatrix();

    // Apply rotation
    float rotationAngle = 48.0f;
    glRotatef(rotationAngle, 0, 0, 1);

    // Apply scaling
    float scaleFactor = 2.0f;
    glScalef(scaleFactor, scaleFactor, 1);

    // Apply reflection
    glScalef(-1, 1, 1);

    // Draw the rotated and scaled square
    drawSquare();

    // Swap buffers to display the rendered image
    glutSwapBuffers();
}

// Program entry point
int main(int argc, char* argv[])
{
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Square");

    // Register callback functions
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    // Set the clear color and enable depth testing
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enter the GLUT event loop
    glutMainLoop();

    return EXIT_SUCCESS;
}
