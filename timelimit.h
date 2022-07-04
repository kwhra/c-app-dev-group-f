#ifndef TIMELIMIT_H
#define TIMELIMIT_H
#include <GL/glut.h>
int getTimeLimit();
void setTimeLimit();
void declineTimeLimit();
GLboolean isTimeUp();
#endif // !TIMELIMIT_H