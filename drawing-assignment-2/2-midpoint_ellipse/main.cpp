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

// Function to draw a pixel at (x, y)
void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to draw an ellipse centered at (0, 0) with given major and minor axis lengths
void drawEllipse(int a, int b)
{
    int x = 0;
    int y = b;

    // Initial decision parameter
    int d = b * b - a * a * b + a * a / 4;

    while (2 * b * b * x <= 2 * a * a * y)
    {
        // Draw 4 symmetric points of the ellipse
        drawPixel(x, y);
        drawPixel(-x, y);
        drawPixel(-x, -y);
        drawPixel(x, -y);

        // Update the decision parameter based on the chosen pixel
        if (d < 0)
        {
            d += b * b * (2 * x + 3);
        }
        else
        {
            d += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            y--;
        }

        x++;
    }

    // Second region
    d = b * b * (x + 1/2) * (x + 1/2) + a * a * (y - 1) * (y - 1) - a * a * b * b;

    while (y >= 0)
    {
        // Draw 4 symmetric points of the ellipse
        drawPixel(x, y);
        drawPixel(-x, y);
        drawPixel(-x, -y);
        drawPixel(x, -y);

        // Update the decision parameter based on the chosen pixel
        if (d < 0)
        {
            d += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
        }
        else
        {
            d += a * a * (-2 * y + 3);
        }

        y--;
    }
}

// Display function to render the scene
static void display(void)
{
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the drawing color to green
    glColor3d(0, 1, 0);

    // Ellipse parameters
    int majorAxis = 200;
    int minorAxis = 100;

    // Draw the ellipse
    drawEllipse(majorAxis, minorAxis);

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
    glutCreateWindow("Midpoint Ellipse");

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
