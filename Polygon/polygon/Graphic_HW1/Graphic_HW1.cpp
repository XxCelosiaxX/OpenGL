/*
*  Name       :  Kulprawee Prayoonsuk
*  Student ID :  105386916
*  Class      :  CSCI 4565
*  HW#        :  1
*  Due Date   :  Feb. 14, 2020
*/

//Necessary Libraries:
#include <GL/glut.h>
#include <vector>

using namespace std;

//window Size 
int WIDTH = 640;
int HEIGHT = 480;

//to store point coordinate
struct point
{
    int x;
    int y;
};

point curPoint;

vector<point> position;		//store all point that was placed

bool RightClick = false;	//flag to keep track of when right mouse is click

//Fill in the shape with solid color
void fill()
{
    glColor3f(0.0, 0.5, 0.5);	//cyan
    glBegin(GL_POLYGON);
    for (int i = 0; i < position.size(); i++)
    {
        glVertex2i(position[i].x, position[i].y);
    }
    glEnd();

    glFlush();
}

//detect mouse click and do the corresponding action 
void draw_polygon(int button, int state, int x, int y)
{
    curPoint.x = x;
    curPoint.y = HEIGHT - y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (RightClick)
            position.clear();	//last action was right click - clear all points
        RightClick = false;
        position.push_back(curPoint);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        RightClick = true;
}

//keep track of current mouse location
void mouse_move(int x, int y)
{
    curPoint.x = x;
    curPoint.y = HEIGHT - y;
    glutPostRedisplay();
}

//display all the elements that been drawn 
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!position.empty())
    {
        glBegin(GL_LINE_STRIP);		//draw group of connected line 
        for (int i = 0; i < position.size(); i++)
        {
            glVertex2f(position[i].x, position[i].y);
        }

        auto& endPt = RightClick ? position.front() : curPoint;
        glVertex2f((float)endPt.x, (float)endPt.y);

        if (RightClick)
        {
            fill();
        }
        glEnd();

        glBegin(GL_POINTS);		//draw points
        {
            for (int i = 1; i < position.size(); i++)
            {
                glVertex2i(position[i - 1].x, position[i - 1].y);
                glVertex2i(position[i].x, position[i].y);
            }
        }
        glEnd();

        glFlush();

    }

    glutSwapBuffers();
}

//initilized all the "setting"
void init()
{
    //set the viewing 
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);

    glClearColor(1, 1, 1, 1);	//white - color when screen is clear
    glColor3f(0.0, 0.5, 0.5); 	//cyan - set color of line and fill
    glPointSize(8.0f);			//set point size
}

//call all the functions
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);	//set window size
    glutInitWindowPosition(100, 100);	//starting location of pop up window
    glutCreateWindow("HW 1 - Kulprawee Prayoonsuk");

    //initilize the functions:
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse_move);
    glutMouseFunc(draw_polygon);
    init();

    glutMainLoop();

    return 0;

}