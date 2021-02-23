//Necessary Libraries:
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define X 0.525731112119133696
#define Z 0.850650808352039932

/* vertex data array */
static GLfloat vdata[12][3] = {
  {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
  {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
  {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};

/* triangle indices */
static int tindices[20][3] = {
  {1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},
  {1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},
  {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
  {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7}
};

struct point
{
    int x;
    int y;
};

point curPoint, startPoint;
int menuOpt, subdivisions = 0;
static int dx = 0, dy = 0;
bool drag = false;
bool shadeMode = true;

GLfloat BlueLightPos[] = { 10.0, 4.0, 10.0, 1.0 };
GLfloat BlueLightColor[] = { 0.0, 0.749, 1.0, 1.0 };          //Deep Sky Blue (right)

GLfloat PinkLightPos[] = { -1.0, -2.0, 1.0, 0.0 };
GLfloat PinkLightColor[] = { 1.000, 0.753, 0.796, 1.0 };       //Pink (left)

GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 1.0,0.0,0.0,1.0 };
GLfloat ambient[] = { 1.0,0.0,0.0,1.0 };
GLfloat shininess = 100.0;

GLboolean BlueToggle = GL_TRUE, PinkToggle = GL_TRUE;


void normalize(GLfloat v[3])
{
    GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[0] /= d; v[1] /= d; v[2] /= d;
}

void normCrossProd(GLfloat u[3], GLfloat v[3], GLfloat n[3])
{
    n[0] = u[1] * v[2] - u[2] * v[1];
    n[1] = u[2] * v[0] - u[0] * v[2];
    n[2] = u[0] * v[1] - u[1] * v[0];
    normalize(n);
}

void normFace(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3])
{
    GLfloat d1[3], d2[3], n[3];
    int k;
    for (k = 0; k < 3; k++)
    {
        d1[k] = v1[k] - v2[k];
        d2[k] = v2[k] - v3[k];
    }
    normCrossProd(d1, d2, n);
    glNormal3fv(n);
}

void drawTriangleFlat(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3])
{

    glBegin(GL_TRIANGLES);
    normFace(v1, v2, v3);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glEnd();
}

void drawTriangleSmooth(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3])
{
    //normal for each vertex
    glBegin(GL_TRIANGLES);
    glNormal3fv(v1);
    glVertex3fv(v1);
    glNormal3fv(v2);
    glVertex3fv(v2);
    glNormal3fv(v3);
    glVertex3fv(v3);
    glEnd();
}

void subdivide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth)
{
    //equallateral triangle can be subdivided into Triforce of courage, wisdom and power
    //depth = how many time to subdivide - can only be subdivide by 4^# starting at 20

    GLfloat v12[3], v23[3], v31[3];
    int i;

    if (depth == 0)
    {
        if (shadeMode)
            drawTriangleFlat(v1, v2, v3);
        else
            drawTriangleSmooth(v1, v2, v3);
        return;
    }

    //find mid point of each side 
    for (i = 0; i < 3; i++) {
        v12[i] = (v1[i] + v2[i]) / 2.0;
        v23[i] = (v2[i] + v3[i]) / 2.0;
        v31[i] = (v3[i] + v1[i]) / 2.0;
    }

    normalize(v12);
    normalize(v23);
    normalize(v31);

    //subdivde recursively 
    subdivide(v1, v12, v31, depth - 1);
    subdivide(v2, v23, v12, depth - 1);
    subdivide(v3, v31, v23, depth - 1);
    subdivide(v12, v23, v31, depth - 1);
}

void display(void)
{
    int i;

    glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glLoadIdentity();
    gluLookAt(0.5, 0.5, -1.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(dx, 1, 0, 0);
    glRotatef(dy, 0, 1, 0);

    for (i = 0; i < 20; i++)
    {
        subdivide(&vdata[tindices[i][0]][0],
            &vdata[tindices[i][1]][0],
            &vdata[tindices[i][2]][0],
            subdivisions);
    }

    glPopMatrix();
    glPopMatrix();

    glFlush();
}

void menu(int opt)
{
    switch (opt)
    {
    case 1:
        BlueToggle = !BlueToggle;
        if (BlueToggle)
        {
            glEnable(GL_LIGHT0);
        }
        else
        {
            glDisable(GL_LIGHT0);
        }
        break;
    case 2:
        PinkToggle = !PinkToggle;
        if (PinkToggle)
        {
            glEnable(GL_LIGHT1);
        }
        else
        {
            glDisable(GL_LIGHT1);
        }
        break;
    case 3:
        shadeMode = !shadeMode;
        break;
    case 4:
        break;
    case 5:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void faceCount(int opt)
{
    switch (opt)
    {
    case 20:
        subdivisions = 0;
        break;
    case 80:
        subdivisions = 1;
        break;
    case 320:
        subdivisions = 2;
        break;
    case 1280:
        subdivisions = 3;
        break;
    }
    glutPostRedisplay();
}

void makeMenu()
{
    int face_menu = glutCreateMenu(faceCount);
    glutAddMenuEntry("20 faces", 20);
    glutAddMenuEntry("80 faces", 80);
    glutAddMenuEntry("320 faces", 320);
    glutAddMenuEntry("1280 faces", 1280);

    glutCreateMenu(menu);
    glutAddMenuEntry("Toggle Blue Light", 1);
    glutAddMenuEntry("Toggle Pink Light", 2);
    glutAddMenuEntry("Toggle Smooth/Flat shadeMode", 3);
    glutAddSubMenu("Change Face Count", face_menu);
    glutAddMenuEntry("Quit", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
}

void mymouse(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        startPoint.x = x;
        startPoint.y = GLUT_WINDOW_HEIGHT - y;
        drag = true;
    }

    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
    {
        drag = false;
    }

    glutPostRedisplay();
}

void reshape(int w, int h)
{
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.25, 1.25, -1.25 * aspect, 1.25 * aspect, -2.0, 2.0);
    else
        glOrtho(-1.25 * aspect, 1.25 * aspect, -1.25, 1.25, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}

void mouse_move(int x, int y)
{
    if (drag)
    {
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

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_LIGHTING);	/* enable lighting */
    glEnable(GL_COLOR_MATERIAL);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glLightfv(GL_LIGHT0, GL_POSITION, BlueLightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, BlueLightColor);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
    glLightfv(GL_LIGHT1, GL_POSITION, PinkLightPos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, PinkLightColor);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialf(GL_LIGHT0, GL_SHININESS, shininess);


    glShadeModel(GL_SMOOTH);

    makeMenu();
    glEnable(GL_DEPTH_TEST); 
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("HW 4 - Kulprawee Prayoonsuk");

    init();

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(mykeyboard);
    glutMouseFunc(mymouse);
    glutMotionFunc(mouse_move);
    glutMainLoop();
    return 0;
}