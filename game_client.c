#include <GL/glut.h>
#include "game.h"
#include "result.h"

//game time (sec)
#define GAME_TIME 3
GLboolean isTimeUp = GL_FALSE;

//func for glutDisplayFunc
// if isTimeUp display Result, else display Gaming 
void main_displayFunc(void){
	if (isTimeUp){
		displayResult();
	}else{
		displayGame();
	}
}

// func for TimeFunc
// if GAMETIME passed, isTimeUp <- true, then ReDisplay
void main_timeFunc(int value){
	isTimeUp = GL_TRUE;
	glutPostRedisplay();
}

// func for idleFunc
void main_idleFunc(){
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Group F");
	glutDisplayFunc(main_displayFunc);
	glutIdleFunc(main_idleFunc);
	glutTimerFunc(GAME_TIME * 1000, main_timeFunc, 0);
	glutMainLoop();
	return 0;
}
