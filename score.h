#ifndef SCORE_H
#define SCORE_H
#include <GL/glut.h>
int getScore(void);
void setScore(int);
void addScore(int);
void damage();
GLboolean gameOver();
#endif // !SCORE_H