#ifndef TIMELIMIT_H
#define TIMELIMIT_H
#include <GL/glut.h>
int getTimeLeft();
void setTimeLeft(int msec);
void declineTimeLeft(int msec);
GLboolean isTimeUp();
#endif // !TIMELIMIT_H