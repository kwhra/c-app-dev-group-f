#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "game.h"
#include "result.h"

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

//display gaming screen
void displayGame(){
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//game screan
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(SCREAN_FOVY, SCREAN_ASPECT, SCREAN_ZNEAR, SCREAN_ZFAR);
	//camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(CAMERA_EYEX, CAMERA_EYEY, CAMERA_EYEZ, CAMERA_CENTERX, CAMERA_CENTERY, CAMERA_CENTERZ, CAMERA_UPX, CAMERA_UPY, CAMERA_UPZ);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0.0, 1.0, 0.0);
	glutSolidSphere(3.0, 20, 20);
	glutSwapBuffers();
}
