#ifndef OBJECT_LOCATION_H
#define OBJECT_LOCATION_H
#include <GL/glut.h>

#define ME 0
// for object type
#define MAIN 0
#define CARROT 1
#define P_CARROT 2
#define DIAMOND 3
//total num
#define OBJECT_NUM 100
typedef struct object{
	// carrot, poison carrot, diamond
	int type;
	GLboolean isVisible;
	//location
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble velocity;
} OBJECT;
void setObjectVelocity(int index, GLdouble v);
GLdouble getObjectVelocity(int index);
void initOBjects();
void setObjectType(int index, int type);
int getObjectType(int index);
void setObjectVisible(int index, GLboolean visible);
GLboolean objectIsVisible(int index);
void setObjectX(int index, GLdouble x);
void setObjectY(int index, GLdouble y);
void setObjectZ(int index, GLdouble z);
GLdouble getObjectX(int index);
GLdouble getObjectY(int index);
GLdouble getObjectZ(int index);
void setObjectLocation(int index, GLdouble x, GLdouble y, GLdouble z);
#endif // !OBJECT_LOCATION_H