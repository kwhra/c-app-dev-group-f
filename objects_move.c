#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include "objects.h"
#include "carrot.h"
#include "objects_draw.h"
#include "head.h"

// width of field
static int D = 5;
// length
static int L = 25;

int sObjectCount = 0;

// 10% diamond, 30% poison carrot, else carrot 
static const double cDiamondRatio = 0;
static const double cPCarrotRatio = 0.3;
static const int starttime = 0;// time until draw first obj
static const int cMakeInterval = 800;// time until draw next obj

static const double cVelocity = 1.0;// velocity

int o_exist;//存在しているか確認

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
	setObjectLocation(index, rand() % D - 2, -1 * L, 1);
	setObjectVisible(index, GL_TRUE);
	if (rand()%RAND_MAX < 0.5)
	{
		setObjectVelocity(index, cVelocity);
	}else{
		setObjectVelocity(index, cVelocity * 1.7);
	}
	
	//type
	double r;
	r = (float)rand() / RAND_MAX;
	if (r < cDiamondRatio)
	{
		setObjectVelocity(index, cVelocity * 2.5);
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
      //printf("object %d is Visible, x:%lf, y:%lf\n", i, getObjectX(i), getObjectY(i));//確認用
			GLdouble tempY = getObjectY(i);
			GLdouble tempV = getObjectVelocity(i);
			setObjectY(i, tempY + tempV);
			if (getObjectY(i) > 0)
			{
        //printf("%lf\n", getObjectY(i));//確認用
				setObjectVisible(i, GL_FALSE);
			}				
		}else{
     //printf("%d is not visible\n", i);//確認用
  }
	}
}

void objectsMove(int passedTime)
{
	if (passedTime > cMakeInterval * sObjectCount)
	{
		makeNewObject(sObjectCount);
	}
	moveObjects(passedTime);
}