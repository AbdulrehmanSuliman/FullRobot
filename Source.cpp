#include <stdlib.h>
#include <glut.h>
#include <iostream>
using namespace std;


static int shoulder = 0, elbow = 0, hand = 0,hand2=0, LegUp = 0, LegUpLeft = 0.0, LegDown=0.0, LegUpL=0.0,LegUpLLeft=0.0,LegDownLeft=0.0;
int moving, startx, starty;
#define PI 3.14

double eye[] = { 0.0, 0.0, 5.0 };
double center[] = { 0.0, 0.0, 0.0 };
double up[] = { 0.0, 1.0, 0.0 };

GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0,
		1.0,
		1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}


void lookRight()
{
	rotatePoint(up, PI / 8, eye);
}

void lookLeft()
{
	//Write your code here
	rotatePoint(up, -PI / 8, eye);
}

// Rotation about horizontal direction

void lookUp()
{
	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, PI / 8, eye);
	rotatePoint(horizontal, PI / 8, up);
}

void lookDown()
{
	//Write your code here
	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, -PI / 8, eye);
	rotatePoint(horizontal, -PI / 8, up);
}

// Forward and Backward
void moveForward()
{
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	float speed = 0.1;
	eye[0] += direction[0] * speed;
	eye[1] += direction[1] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
}

void moveBackword()
{
	//Write your code here
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	float speed = 0.1;
	eye[0] -= direction[0] * speed;
	eye[1] -= direction[1] * speed;
	eye[2] -= direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;
}




void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		up[0], up[1], up[2]);
	glPushMatrix();
	glScalef(0.75, 0.75, 0.75);
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(-1.0, 0.0, 0.0);
	
	//body
	
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, 1.5, 0.5);
	glutWireCube(2.0);


	glPopMatrix();
	
	//Head
	
	glPushMatrix();
	glTranslatef(0.0, 2.0, 0.0);
	glutWireSphere(0.5,5,5);
	glPopMatrix();
	
	//Shoulder1

	glPushMatrix();
	glTranslatef(1.25, 1.25, 0.0);
	glScalef(0.75, 0.75, 0.75);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)hand, 1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//Draw finger flang 1
	glPushMatrix();
	glTranslatef(1.15, 0.25, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();


	//Draw finger flang 1 
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	//Draw finger flang 2 
	glTranslatef(1.15, 0.25, 0.45);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();

	//Draw finger flang 2 
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	//Draw finger flang 3
	glPushMatrix();
	glTranslatef(1.15, 0.25, -0.45);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();


	//Draw finger flang 3 
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	//Draw finger flang 4
	glPushMatrix();
	glTranslatef(1.15, -0.25, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();


	//Draw finger flang 4 
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	
	//Shoulder2

	glPushMatrix();
	glTranslatef(-1.25, 1.25, 0.0);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.75, 0.75, 0.75);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)hand2, 1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//Draw finger flang 1
	glPushMatrix();
	glTranslatef(1.15, 0.25, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();


	//Draw finger flang 1 
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	//Draw finger flang 2 
	glTranslatef(1.15, 0.25, 0.45);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();

	//Draw finger flang 2 
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	//Draw finger flang 3
	glPushMatrix();
	glTranslatef(1.15, 0.25, -0.45);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();


	//Draw finger flang 3 
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	//Draw finger flang 4
	glPushMatrix();
	glTranslatef(1.15, -0.25, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();


	//Draw finger flang 4 
	glTranslatef(0.3, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	
	//Leg1
	
	glPushMatrix();
	glTranslatef(0.375, -1.3, 0.0);
	glRotatef((GLfloat)LegUp, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)LegUpLeft, 0.0, 0.0, 1.0);
	glTranslatef(0.375, -1.2, 0.0);

	glPushMatrix();
	glScalef(0.5, 2.0, 0.75);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -1.0, 0.0);
	glRotatef((GLfloat)LegDown, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);

	glPushMatrix();
	glScalef(0.5, 2.0, 0.75);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -1.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.5, 1.25);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	
	//Leg2

	glPushMatrix();
	glTranslatef(-0.375, -1.3, 0.0);
	glRotatef((GLfloat)LegUpL, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)LegUpLLeft, 0.0, 0.0, 1.0);
	glTranslatef(-0.375, -1.2, 0.0);

	glPushMatrix();
	glScalef(0.5, 2.0, 0.75);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -1.0, 0.0);
	glRotatef((GLfloat)LegDownLeft, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);

	glPushMatrix();
	glScalef(0.5, 2.0, 0.75);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -1.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.5, 1.25);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	
	
	

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
void reset()
{
	double e[] = { 0.0, 0.0, 5.0 };
	double c[] = { 0.0, 0.0, 0.0 };
	double u[] = { 0.0, 1.0, 0.0 };
	for (int i = 0; i < 3; i++)
	{
		eye[i] = e[i];
		center[i] = c[i];
		up[i] = u[i];
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		if (shoulder >= -90)
		{
			shoulder = (shoulder - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'S':
		if (shoulder <= 90)
		{
			shoulder = (shoulder + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'e':
		if (elbow >-90)
		{
			elbow = (elbow - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'E':
		if (elbow <0)
		{
			elbow = (elbow + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'h':
		if (hand >= -180 )
			hand = (hand - 5) % 360;
		if (hand2 <=180)
			hand2 = (hand2 + 5) % 360;
		
		
		glutPostRedisplay();
		break;
	case 'H':
		if (hand <= 0 )
			hand = (hand + 5) % 360;
		if (hand2 >= 0)
			hand2 = (hand2 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'l':
		if (LegUp >= -90)
			LegUp = (LegUp - 5) % 360;
		glutPostRedisplay();
		break;
	case 'L':
		if (LegUp < 90)
			LegUp = (LegUp + 5) % 360;
	
		glutPostRedisplay();
		break;
	case 'y':
		if (LegUpL >= -90)
			LegUpL = (LegUpL - 5) % 360;
		glutPostRedisplay();
		break;
	case 'Y':
		if (LegUpL < 90)
			LegUpL = (LegUpL + 5) % 360;

		glutPostRedisplay();
		break;

	case 'k':
		if(LegUpLeft<=50)
			LegUpLeft = (LegUpLeft + 5) % 360;
		glutPostRedisplay();
		break;
	case 'K':
		if (LegUpLeft > 0)
			LegUpLeft = (LegUpLeft - 5) % 360;
		glutPostRedisplay();
		break;
	case 'q':
		if (LegUpLLeft >= -50)
			LegUpLLeft = (LegUpLLeft - 5) % 360;
		glutPostRedisplay();
		break;
	case 'Q':
		if (LegUpLLeft < 0)
			LegUpLLeft = (LegUpLLeft + 5) % 360;
		glutPostRedisplay();
		break;

	case 'd':
		if(LegDown<=90)
		LegDown = (LegDown + 5) % 360;
		glutPostRedisplay();
		break;
	case 'D':
		if (LegDown > 0)
			LegDown = (LegDown - 5) % 360;
		glutPostRedisplay();
		break;
	case 'r':
		if (LegDownLeft <= 90)
			LegDownLeft = (LegDownLeft + 5) % 360;
		glutPostRedisplay();
		break;
	case 'R':
		if (LegDownLeft > 0)
			LegDownLeft = (LegDownLeft - 5) % 360;
		glutPostRedisplay();
		break;
	case 'f':
		moveForward();
		glutPostRedisplay();
		break;
	case 'b':
		moveBackword();
		glutPostRedisplay();
		break;
	case 'a':
		reset();
		glutPostRedisplay();
		break;

	case 27:
		exit(0);
		break;
	default:
		break;
	}
}



void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		lookLeft();
		break;
	case GLUT_KEY_RIGHT:
		lookRight();
		break;
	case GLUT_KEY_UP:
		lookUp();
		break;
	case GLUT_KEY_DOWN:
		lookDown();
		break;
	}
	glutPostRedisplay();
}






static void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP) {
			moving = 0;
		}
	}
}


static void motion(int x, int y)
{
	if (moving) {
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
