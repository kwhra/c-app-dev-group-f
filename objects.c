#include <GL/glut.h>
#include "objects.h"


// OBJECT = {int type; GLboolean isVisible; GLdouble* location}
static OBJECT sObjects[OBJECT_NUM];

void initOBjects(){
	// for i = 1 ~
	// initialize 0
	int i;
	for (i = 0; i < OBJECT_NUM; i++){
		sObjects[i].type = 0;
		sObjects[i].isVisible = GL_FALSE;
		sObjects[i].x = 0.0;
		sObjects[i].y = 0.0;
		sObjects[i].z = 0.0;
	}
}

void setObjectType(int index, int type){
	sObjects[index].type = type;
}

int getObjectType(int index){
	return sObjects[index].type;
}

void setObjectVisible(int index, GLboolean visible){
	sObjects[index].isVisible = visible;
}

GLboolean objectIsVisible(int index){
	return sObjects[index].isVisible;
}

void setObjectX(int index, GLdouble x){
	sObjects[index].x = x;
}
void setObjectY(int index, GLdouble y){
	sObjects[index].y = y;
}
void setObjectZ(int index, GLdouble z){
	sObjects[index].z = z;
}

void setObjectLocation(int index, GLdouble x, GLdouble y, GLdouble z){
	setObjectX(index, x);
	setObjectY(index, y);
	setObjectZ(index, z);
}

GLdouble getObjectX(int index){
	return sObjects[index].x;
}
GLdouble getObjectY(int index){
	return sObjects[index].y;
}
GLdouble getObjectZ(int index){
	return sObjects[index].z;
}

