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
    glOrtho(0, width, 0, height, -1, 1);

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

// Function to draw a line from (x1, y1) to (x2, y2)
void drawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

// Function to draw a circle centered at (centerX, centerY) with a given radius using Bresenham's Circle Algorithm
void drawCircle(int centerX, int centerY, int radius)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y)
    {
        // Draw 8 symmetric points on the circle
        drawPixel(centerX + x, centerY + y);
        drawPixel(centerX + y, centerY + x);
        drawPixel(centerX - x, centerY + y);
        drawPixel(centerX + y, centerY - x);
        drawPixel(centerX - x, centerY - y);
        drawPixel(centerX - y, centerY - x);
        drawPixel(centerX + x, centerY - y);
        drawPixel(centerX - y, centerY + x);

        // Update the decision parameter
        if (d < 0)
        {
            d += 4 * x + 6;
        }
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

// Display function to render the scene
static void display(void)
{
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the drawing color to red
    glColor3d(1, 0, 0);

    // Circle parameters
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int radius = 160;

    // Draw the circle
    drawCircle(centerX, centerY, radius);

    // Set the drawing color to black
    glColor3d(0, 0, 0);

    // Draw the diameter line
    int x1 = centerX - radius;
    int y1 = centerY;
    int x2 = centerX + radius;
    int y2 = centerY;
    drawLine(x1, y1, x2, y2);

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
    glutCreateWindow("Bresenham's Circle");

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
