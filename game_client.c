#include <GL/glut.h>
#include <stdio.h>
#include "game.h"
#include "result.h"
#include "timeleft.h"
#include "objects_move.h"
#include "player.h"
#include "score.h"

// timelimit (msec)
static int sTimeLimit = 60;
// Redisplay interval for TimeFunc (msec)
static const int cRedisplayInterval = 50;

//func for glutDisplayFunc
// if isTimeUp or gameup, then display Result, else display Gaming 
void main_displayFunc(void){   
	 if (isTimeUp() || gameOver() ){
     //printf("time up!!\n");
	   displayResult();     
	 }else{
		 displayGame();
   }
}

// func for TimeFunc
// if GAMETIME passed, then isTimeUp <- true, else ReDisplay
void main_timeFunc(int passedTime){
	declineTimeLeft(cRedisplayInterval);
	if (!(isTimeUp() || gameOver())){
		idle();
		objectsMove(passedTime);
	}
	glutPostRedisplay();
	glutTimerFunc(cRedisplayInterval, main_timeFunc, passedTime + cRedisplayInterval);
}

// func for idleFunc
void main_idleFunc(){
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	printf("input TimeLimit [sec]: ");
	scanf("%d", &sTimeLimit);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Group F");
	glutDisplayFunc(main_displayFunc);
	initGame();
	glutIdleFunc(main_idleFunc);
	glutTimerFunc(cRedisplayInterval, main_timeFunc, 0);
	setTimeLeft(sTimeLimit*1000);
	glutMainLoop();
	return 0;
}
