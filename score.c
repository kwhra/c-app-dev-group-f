#include "score.h"
#include <GL/glut.h>
static int sScore = 0;
int getScore(){
	return sScore;
}
void setScore(int score){
	sScore = score;
}
void addScore(int points){
	sScore += points;
}

static int sLife = 3;
void damage(){
	sLife--;
}
GLboolean gameOver(){
	if(sLife<1){
		return GL_TRUE;
	}else{
		return GL_FALSE;
	}
}