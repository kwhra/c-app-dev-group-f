#include <GL/glut.h>
#include <time.h>
#include "objects.h"
#include "carrot.h"
#include "objects_draw.h"

// width of field
int D = 10;
// height
int H = 10;
// length
int L = 15;

int sObjectCount = 0;

// 10% diamond, 30% poison carrot, else carrot 
static const double cDiamondRatio = 0;
static const double cPCarrotRatio = 0.4;
static const int starttime = 5;// time until draw first obj
static const int interval = 10;// time until draw next obj


void drawobjects (void)
{
	for(int i = 0; i < sObjectCount; i++)
	{
		if(objectIsVisible(i))
		{
			glPushMatrix();
			glTranslatef(getObjectX(i), getObjectY(i), getObjectZ(i));
			drawObject(i);
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

static void objectMake(int index){
	srand((unsigned int)time(NULL));
	setObjectLocation(index, rand() % D - 5, -1 * L, 0);
	setObjectVisible(index, GL_TRUE);

	//type
	double r;
	r = (float)rand() / RAND_MAX;
	if (r < cDiamondRatio)
	{
		setObjectType(index, DIAMOND);
	}
	else if (r < cPCarrotRatio)
	{
		setObjectType(index, P_CARROT);
	}
	else
	{
		setObjectType(index, CARROT);
	}
}

void objectmove(int t)
{
	if (t > 0)
	{
		double v = 1;// velocity

		if ((t - starttime) % interval == 0)
		{
			// decide obj type, and location
			int index = (t - starttime) / interval;
			objectMake(index);
		}

		// exceed 1 step
		// if y>5, delete
		for (int i = 0; i < (t - starttime) / interval; i++)
		{
			if (objectIsVisible(i))
			{
				GLdouble tempY = getObjectY(i);
				setObjectY(i, tempY + v);
				if (getObjectY(i) > 5)
				{
					setObjectVisible(i, GL_FALSE);
				}				
			}
			
		}

		sObjectCount = (t - starttime) / interval + 1;

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
