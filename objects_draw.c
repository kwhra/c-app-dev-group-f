#include <GL/glut.h>
#include "objects.h"
#include "carrot.h"
#include "diamond.h"

static const GLdouble size = 0.5;

void drawObject(int index){
	if (objectIsVisible(index)){
		glPushMatrix();
		glScaled(size, size, size);
		switch (getObjectType(index)){
		case CARROT:
			drawCarrot();
			break;
		case P_CARROT:
			drawPoisonCarrot();
			break;
		case DIAMOND:
			drawDiamond();
			break;
		default:
			break;
		}
		glPopMatrix();
	}
}