#include "perlin.h"
#include "simplex.h"

int terrain_dimension = 1000;
vector<vector<float>> test(terrain_dimension, vector<float>(terrain_dimension));

void myinit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499.0, 0.0, 499.0);

}

void draw_raster_image(vector<vector<float>>& wireframe) 
{
    glBegin(GL_POINTS);

    for (GLint i = 0; i < terrain_dimension; ++i) {
        for (GLint j = 0; j < terrain_dimension; ++j) {

            GLfloat c = test[i][j];

            glColor3f(c, c, c);

            glVertex2i(i, j);

        }
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    draw_raster_image(test);

    glFlush();
}

float convertRange(float old)
{
    float oldPercent;
    float newVal;

    oldPercent = (old - (-1)) / (1 - (-1));
    newVal = ((1 - 0) * oldPercent) + 0;

    return newVal;
}

int main(int argc, char** argv) {

    float scale = .007;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < terrain_dimension; ++i) {
        for (int j = 0; j < terrain_dimension; ++j) {
            //test[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);   //random 0.0 to 1.0, inclusive
            //test[i][j] = perlin2d(i*0.2, j*.2, 0.5, 8);                                    //perlin (x,y,frquency, depth) parameters x and y are the position in the noise function, freq is the frequency of the noise function, and depth is the number of samples to generate.
            test[i][j] = convertRange(noise(i * scale, j * scale));                      //simplex scale [-1,1] to [0,1]
        }
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration <double, milli>(diff).count() << "ms" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Height Map");
    glutDisplayFunc(display);

    myinit();
    glutMainLoop();

    return 0;
}