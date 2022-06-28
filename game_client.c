#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

//game time (sec)
#define GAME_TIME 3

//program dialogue screan
#define SCREAN_FOVY 100.0
#define SCREAN_ASPECT 1.0
#define SCREAN_ZNEAR 1.0
#define SCREAN_ZFAR 100.0

//camera
#define CAMERA_EYEX 0.0
#define CAMERA_EYEY 10.0
#define CAMERA_EYEZ 10.0
#define CAMERA_CENTERX 0.0 
#define CAMERA_CENTERY 0.0
#define CAMERA_CENTERZ 0.0
#define CAMERA_UPX 0.0
#define CAMERA_UPY 0.0
#define CAMERA_UPZ 1.0

GLboolean isTimeUp = GL_FALSE;

//display gaming screen
void displayGame(){
	glColor3d(0.0, 1.0, 0.0);
	glutSolidSphere(3.0, 20, 20);
}

//display result screan
void displayResult(){
	glColor3d(0.0, 1.0, 0.0);
	glutSolidCube(5.0);
}

//func for glutDisplayFunc
// if isTimeUp display Result, else display Gaming 
void main_displayFunc(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (isTimeUp) {
		displayResult();
	}else{
		displayGame();
	}
	glutSwapBuffers();
}

//init func
void main_initFunc(void){
	isTimeUp = GL_FALSE;
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//game screan
	gluPerspective(SCREAN_FOVY, SCREAN_ASPECT, SCREAN_ZNEAR, SCREAN_ZFAR);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//camera
	gluLookAt(CAMERA_EYEX, CAMERA_EYEY, CAMERA_EYEZ, CAMERA_CENTERX, CAMERA_CENTERY, CAMERA_CENTERZ, CAMERA_UPX, CAMERA_UPY, CAMERA_UPZ);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
}

// func for TimeFunc
// if GAMETIME passed, isTimeUp <- true, then ReDisplay
void main_timeFunc(int value){
	isTimeUp = GL_TRUE;
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Group F");
	glutDisplayFunc(main_displayFunc);
	main_initFunc();
	glutTimerFunc(GAME_TIME * 1000, main_timeFunc, 0);
	glutMainLoop();
	return 0;
}
