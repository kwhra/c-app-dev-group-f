#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "result.h"
#include "objects_move.h"

//program dialogue screan
#define SCREAN_FOVY 100.0
#define SCREAN_ASPECT 1.0
#define SCREAN_ZNEAR 1.0
#define SCREAN_ZFAR 100.0

//camera
#define CAMERA_EYEX 0.0
#define CAMERA_EYEY 5.0
#define CAMERA_EYEZ 2.0
#define CAMERA_CENTERX 0.0 
#define CAMERA_CENTERY 0.0
#define CAMERA_CENTERZ 0.0
#define CAMERA_UPX 0.0
#define CAMERA_UPY 0.0
#define CAMERA_UPZ 1.0

//display gaming screen
void initGame(){
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//game screan
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, .1, 100.0);
	//gluPerspective(SCREAN_FOVY, SCREAN_ASPECT, SCREAN_ZNEAR, SCREAN_ZFAR);
	//camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10.0, 4.0, 0.0, -10.0, 0.0, 0.0, 0.0, 1.0);
	//gluLookAt(CAMERA_EYEX, CAMERA_EYEY, CAMERA_EYEZ, CAMERA_CENTERX, CAMERA_CENTERY, CAMERA_CENTERZ, CAMERA_UPX, CAMERA_UPY, CAMERA_UPZ);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glColor3d(1.0, 1.0, 1.0);
}

void displayGame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	drawObjects();
	glPopMatrix();
	glutSwapBuffers();
}
