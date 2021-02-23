/*
*  Name       :  Kulprawee Prayoonsuk
*  Student ID :  105386916
*  Class      :  CSCI 4565
*  HW#        :  3
*  Due Date   :  March 6, 2020
*/

/**
 *  teaambient.c
 *  This program renders three lighted, shaded teapots, with
 *  different ambient values.
 */

 //Necessary Libraries:
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

//varibles
static int dx = 0, dy = 0, menuOpt = 0, value = 9;
bool grid = true;
bool drag = false;

struct point
{
    int x;
    int y;
};

point curPoint;
point startPoint;

void menu(int num)
{
    if (num == 0)
    {
        cout << "Thank you!" << endl;
        exit(0);
    }
    else
        value = num;
    
    grid = !grid;

    glutPostRedisplay();
}

void makeMenu()
{
    menuOpt = glutCreateMenu(menu);
    glutAddMenuEntry("Toggle Grid", 1);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mymouse(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
            //cout << "drag on" << endl;
            startPoint.x = x;
            startPoint.y = GLUT_WINDOW_HEIGHT - y;
            drag = true;
    }
    
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
    {
        //cout << "drag off" << endl;
        drag = false;
    }

    glutPostRedisplay();
}

void ro()
{
   
    if (startPoint.x > curPoint.x)
    {
        dy -= 3;
    }

    if (startPoint.x < curPoint.x)
    {
        dy += 3;
    }

    if (startPoint.y > curPoint.y)
    {
        dx -= 3;
    }

    if (startPoint.y < curPoint.y)
    {
        dx += 3;
    }


    //glutPostRedisplay();
}

void mouse_move(int x, int y)
{
    //cout << "passive" << endl;
    if(drag)
    {
        //cout << "here" << endl;
        curPoint.x = x;
        curPoint.y = GLUT_WINDOW_HEIGHT - y;

        ro();

        startPoint.x = x;
        startPoint.y = GLUT_WINDOW_HEIGHT - y;

        glutPostRedisplay();
    }
}

void mykeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        dx -= 5;
        break;
    case 's':
        dx += 5;
        break;
    case 'a':
        dy -= 5;
        break;
    case 'd':
        dy += 5;
    default:
        break;
    }

    glutPostRedisplay();
}
/*  Initialize light source and lighting model.*/
void myinit(void)
{

    GLfloat light_ambient[] =
    { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] =
    { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] =
    { 1.0, 1.0, 1.0, 1.0 };
    /* light_position is NOT default value */
    GLfloat light_position[] =
    { 1.0, 1.0, 0.0, 0.0 };
    GLfloat global_ambient[] =
    { 0.75, 0.75, 0.75, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void drawGrid()
{
    glColor3f(1.0, 1.0, 1.0);

    // 1st grid
    glBegin(GL_LINES);
    for (float i = -2.0; i < 2.0; i += 0.1)
    {
        glVertex3f(0.0f, 2.0f, i);
        glVertex3f(0.0f, -2.0f, i);
    }
    glEnd();

    glBegin(GL_LINES);
    for (float i = -2.0; i < 2.0; i += 0.1)
    {
        glVertex3f(0.0f, i, -2.0f);
        glVertex3f(0.0f, i, 2.0f);
    }
    glEnd();

    // 2nd grid
    
    glBegin(GL_LINES);
    for (float i = -2.0; i < 2.0; i += 0.1)
    {
        glVertex3f(i, 2.0f, 0);
        glVertex3f(i, -2.0f, 0);
    }
    glEnd();

    glBegin(GL_LINES);
    for (float i = -2.0; i < 2.0; i += 0.1)
    {
        glVertex3f(0.0f, i, 0.0f);
        glVertex3f(0.0f, i, 0.0f);
    }
    glEnd();

    // 3rd grid
    glBegin(GL_LINES);
    for (float i = -2.0; i < 2.0; i += 0.1)
    {
        glVertex3f(-2.0f, 0.0f, i);
        glVertex3f(2.0f, 0.0f, i);
    }
    glEnd();

    glBegin(GL_LINES);
    for (float i = -2.0; i < 2.0; i += 0.1)
    {
        glVertex3f(i,0.0f,-2.0f);
        glVertex3f(i,0.0f,2.0f);
    }
    glEnd();

}

void display(void)
{
    glPushMatrix();

    GLfloat low_ambient[] =
    { 0.1, 0.1, 0.1, 1.0 };
    GLfloat more_ambient[] =
    { 0.4, 0.4, 0.4, 1.0 };
    GLfloat most_ambient[] =
    { 1.0, 1.0, 1.0, 1.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    /*  material has moderate ambient reflection */
    glMaterialfv(GL_FRONT, GL_AMBIENT, more_ambient);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, -1, 0, 1, 0);


    glRotatef(dx, 1, 0, 0);
    glRotatef(dy, 0, 1, 0);

    glutSolidTeapot(1.0);
    if (value == 1)
    {
        if (grid == false)
        {
            //grid on
            //cout << "grid on" << endl;
            drawGrid();
        }

        else
        {
            //grid off
            //cout << "grid off" << endl;
        }
    }
    glPopMatrix();

    glPopMatrix();
    glFlush();

}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat)w / (GLfloat)h, 1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}


/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("HW 3 - Kulprawee Prayoonsuk");
    cout << "Kulprawee Prayoonsuk - HW 3 - Tea Pot Rotation" << endl;
    cout << "My favorite Tea is Green Tea" << endl;
    cout << "What is your?" << endl;
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(mykeyboard);
    glutMouseFunc(mymouse);
    glutMotionFunc(mouse_move);
    makeMenu();
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}