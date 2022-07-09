#include <GL/glut.h>
#include "game.h"
#include "result.h"
#include "timeleft.h"
#include "objects_move.h"

// timelimit (msec)
static const int cTimeLimit = 1 * 1000;
// Redisplay interval for TimeFunc (msec)
static const int cRedisplayInterval = 50;

//func for glutDisplayFunc
// if isTimeUp display Result, else display Gaming 
void main_displayFunc(void){
	if (isTimeUp()){
		displayResult();
	}else{
		displayGame();
	}
}

// func for TimeFunc
// if GAMETIME passed, isTimeUp <- true, then ReDisplay
void main_timeFunc(int passedTime){
	declineTimeLeft(cRedisplayInterval);
	objectsMove(passedTime);
	glutPostRedisplay();
	glutTimerFunc(cRedisplayInterval, main_timeFunc, passedTime + cRedisplayInterval);
}

// func for idleFunc
void main_idleFunc(){
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	setTimeLeft(cTimeLimit);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Group F");
	glutDisplayFunc(main_displayFunc);
	glutIdleFunc(main_idleFunc);
	glutTimerFunc(cRedisplayInterval, main_timeFunc, 0);
	glutMainLoop();
	return 0;
}
