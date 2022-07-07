#include <GL/glut.h>
#include "objects.h"
#include "carrot.h"
#include "diamond.h"

void drawObject(int index){
	if (objectIsVisible(index)){
		switch (getObjectType(index)){
		case ME:
			//drawMe();
			break;
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
	}
}