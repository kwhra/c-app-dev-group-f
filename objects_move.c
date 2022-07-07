#include <GL/glut.h>
#include <time.h>
#include "objects.h"
#include "carrot.h"
#include "objects_draw.h"

GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};

// width of field
int D = 10;
// height
int H = 10;
// length
int L = 15;

int T;

void drawobjects (void)
{
	for(int i = 0; i < T; i++)
	{
		if(objectIsVisible(i))
		{
			glPushMatrix();
			glTranslatef(getObjectX(i), getObjectY(i), getObjectZ(i));
			drawCarrot();
			glPopMatrix();
		}
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawobjects();

	glPopMatrix();
	glutSwapBuffers();
}


void objectmove(int t)
{
	if (t > 0)
	{

		srand((unsigned int)time(NULL) + t);//initialize randseed

		int starttime = 5;// time until draw first obj
		int interval = 10;// time until draw next obj

		double v = 1;// velocity

		if ((t - starttime) % interval == 0)
		{
			// decide obj type, and location
			int index = (t - starttime) / interval;
			setObjectLocation(index, rand() % D - 5, -1 * L, rand() % H);
			setObjectVisible(index, GL_TRUE);

			//type
			double r;
			double p = 0.6;// 60% carrot, else poison carrot
			r = (float)rand() / RAND_MAX;
			if (r < p)
			{
				setObjectType(index, CARROT);
			}
			else
			{
				setObjectType(index, P_CARROT);
			}
		}

		// exceed 1 step
		// if y>5, delete
		for (int i = 0; i < (t - starttime) / interval; i++)
		{
			GLdouble tempY = getObjectY(i);
			setObjectY(i, tempY + v);
			if (getObjectY(i) > 5)
			{
				setObjectVisible(i, GL_FALSE);
			}
		}

		T = (t - starttime) / interval + 1;

	}

	glutTimerFunc(50, objectmove, t + 1);

}

void idle(void)
{
	glutPostRedisplay();
}

void init(void)
{
	initOBjects();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutIdleFunc(idle);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, .1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.6, 8.2, 0.0, -10.0, 4.0, 0.0, 0.0, 1.0);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("C Dev");
	glutDisplayFunc(display);
	objectmove(0);
	init();
	glutMainLoop();
	return 0;
}
