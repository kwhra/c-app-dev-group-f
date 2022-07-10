#include <GL/glut.h>
#include <time.h>
#include "objects.h"
#include "carrot.h"
#include "objects_draw.h"

// width of field
static int D = 5;
// length
static int L = 25;

static int sObjectCount = 0;

// 10% diamond, 30% poison carrot, else carrot 
static const double cDiamondRatio = 0;
static const double cPCarrotRatio = 0.4;
static const int starttime = 0;// time until draw first obj
static const int cMakeInterval = 1000;// time until draw next obj
static const int cMoveInterval = 100;

static const double cVelocity = 1;// velocity

void drawObjects ()
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

static void makeNewObject(int index){
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
	sObjectCount++;
	if(sObjectCount == OBJECT_NUM){
		sObjectCount = 0;
	}
}

static void moveObjects(int passedTime){
	// exceed 1 step
	// if y>5, delete
	for (int i = 0; i < sObjectCount; i++)
	{
		if (objectIsVisible(i))
		{
			GLdouble tempY = getObjectY(i);
			setObjectY(i, tempY + cVelocity);
			if (getObjectY(i) > 1)
			{
				setObjectVisible(i, GL_FALSE);
			}				
		}
	}
}

void objectsMove(int passedTime)
{
	if ((passedTime) % cMakeInterval == 0)
	{
		makeNewObject(sObjectCount);
	}
	if ((passedTime) % cMoveInterval == 0)
	{
		moveObjects(passedTime);
	}
}