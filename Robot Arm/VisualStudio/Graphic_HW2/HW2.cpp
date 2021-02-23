/*
*  Name       :  Kulprawee Prayoonsuk
*  Student ID :  105386916
*  Class      :  CSCI 4565
*  HW#        :  2
*  Due Date   :  Feb. 26, 2020
*/

/*
Keyboard commands:
(Clockwise / Counterclock wise)
s/S - shoulder
e/E - elbow
h/H - hand(wrist)
1/! - finger 1
2/@ - finger 2
3/# - finger 3
*/

//Necessary Libraries:
#include <GL/glut.h>

static int shoulder = 0, elbow = 0, hand = 0, f1 = 0, f2 = 0, f3 = 0;

//Elbow
void elbowAdd(void)
{
	elbow = (elbow + 5) % 360;
}

void elbowSubtract(void)
{
	elbow = (elbow - 5) % 360;
}

//Shoulder
void shoulderAdd(void)
{
	shoulder = (shoulder + 5) % 360;
}

void shoulderSubtract(void)
{
	shoulder = (shoulder - 5) % 360;
}

//Hand
void handAdd(void)
{
	hand = (hand + 5) % 360;
}

void handSubtract(void)
{
	hand = (hand - 5) % 360;
}

//Finger 1
void f1Add(void)
{
	f1 = (f1 + 5) % 360;
}

void f1Subtract(void)
{
	f1 = (f1 - 5) % 360;
}

//Finger 2
void f2Add(void)
{
	f2 = (f2 + 5) % 360;
}

void f2Subtract(void)
{
	f2 = (f2 - 5) % 360;
}

//Finger 3
void f3Add(void)
{
	f3 = (f3 + 5) % 360;
}

void f3Subtract(void)
{
	f3 = (f3 - 5) % 360;
}
//-------------------------------------------------------------------

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();

	/* shoulder */
	glTranslatef(-1.0, 0.0, 0.0);	//the origin of where it will rotate about
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);	//the placement will be first translate + second 
	//push new matrix - that why it only scale this current matrix
	glPushMatrix();
	glScaled(0.5, 0.3, 0.5);
	glutWireCube(2.0);
	glPopMatrix();

	/* elbow */
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.5, 0.3, 0.5);
	glTranslatef(-.0, 0.0, 0.0);
	glutWireCube(2.0);
	glPopMatrix();

	/* hand*/
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.5, 0.3, 0.5);
	glutWireCube(2.0);
	glPopMatrix();

	glPushMatrix();		//the finger need extra push and pop to make it start in the hand matrix
	/* f1*/
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef((GLfloat)f1, 0.0, 0.0, 1.0);
	glTranslatef(0.18, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.3, 0.2, 0.3);
	glutWireCube(1.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	/* f2*/

	glTranslatef(0.5, 0.0, 0.0);
	glRotatef((GLfloat)f2, 0.0, 0.0, 1.0);
	glTranslatef(0.18, 0.0, 0.3);
	glPushMatrix();
	glScaled(0.3, 0.2, 0.3);
	glutWireCube(1.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	/* f3*/

	glTranslatef(0.5, 0.1, 0.0);							
	glRotatef((GLfloat)f3, 0.0, 0.0, 1.0);
	glTranslatef(0.18, 0.1, 0.0);
	glPushMatrix();
	glScaled(0.3, 0.2, 0.3);
	glutWireCube(1.0);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	glFlush();
}

//-------------------------------------------------------------------

void myinit(void)
{
	glShadeModel(GL_FLAT);
}

//-------------------------------------------------------------------
void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);	//set view port 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

//-------------------------------------------------------------------
//keyboard input
void mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'S':
		shoulderAdd();
		break;
	case 's':
		shoulderSubtract();
		break;
	case 'E':
		elbowAdd();
		break;
	case 'e':
		elbowSubtract();
		break;
	case 'H':
		handAdd();
		break;
	case 'h':
		handSubtract();
		break;
	case '1':
		f1Add();
		break;
	case '!':
		f1Subtract();
		break;
	case '2':
		f2Add();
		break;
	case '@':
		f2Subtract();
		break;
	case '3':
		f3Add();
		break;
	case '#':
		f3Subtract();
		break;
	default:
		break;
	}
	glutPostRedisplay();		//redisplay the screen after each key press
}

//-------------------------------------------------------------------
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Kulprawee Prayoonsuk - HW2 - Robot Hand");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(mykeyboard);
	glutMainLoop();
}