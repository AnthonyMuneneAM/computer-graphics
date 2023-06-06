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

    // Decision parameters
    int a2 = a * a;
    int b2 = b * b;
    int twoA2 = 2 * a2;
    int twoB2 = 2 * b2;
    int d = b2 - a2 * b + 0.25 * a2;

    int dx = 0;
    int dy = twoA2 * y;

    while (dx <= dy)
    {
        // Draw 4 symmetric points of the ellipse
        drawPixel(x, y);
        drawPixel(-x, y);
        drawPixel(-x, -y);
        drawPixel(x, -y);

        // Update the decision parameter based on the chosen pixel
        if (d < 0)
        {
            dx += twoB2;
            d += dx + b2;
        }
        else
        {
            dx += twoB2;
            dy -= twoA2;
            d += dx - dy + b2;
            y--;
        }

        x++;
    }

    // Decision parameters
    d = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;

    while (y >= 0)
    {
        // Draw 4 symmetric points of the ellipse
        drawPixel(x, y);
        drawPixel(-x, y);
        drawPixel(-x, -y);
        drawPixel(x, -y);

        // Update the decision parameter based on the chosen pixel
        if (d > 0)
        {
            dy -= twoA2;
            d += a2 - dy;
        }
        else
        {
            dy -= twoA2;
            dx += twoB2;
            d += a2 + dx - dy;
            x++;
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
    glutCreateWindow("Bresenham's Ellipse");

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
