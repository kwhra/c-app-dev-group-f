#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "result.h"
#include "objects_move.h"
#include "head.h"
#include "player.h"

//program dialogue screan
#define SCREAN_FOVY 30
#define SCREAN_ASPECT 1.0
#define SCREAN_ZNEAR 0.1
#define SCREAN_ZFAR 100.0

//camera
#define CAMERA_EYEX 0.0
#define CAMERA_EYEY 10.0
#define CAMERA_EYEZ 4.0
#define CAMERA_CENTERX 0.0 
#define CAMERA_CENTERY -10.0
#define CAMERA_CENTERZ 0.0
#define CAMERA_UPX 0.0
#define CAMERA_UPY 0.0
#define CAMERA_UPZ 1.0

//display gaming screen
void initGame(){
	glClearColor(0.5, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpcialFunc);
	glutSpecialUpFunc(mySpcialUpFunc);
  glutMouseFunc(myMouseFunc);
	glutPassiveMotionFunc(myPassiveMotionFunc);
	
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
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color[WHITE]);
	glColor3d(1.0, 1.0, 1.0);
}

void displayGame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
  glPushMatrix();
  
  if(hit > 2){//hitしたら表示する(hitを0~5にすることで表示時間の調整をした)一番最初に置いたほうが良い(バグったので)
    printString(0.5, -0.5, "Great!!", 7);
  }
  //glPopMatrix(); 
  
  
  drawGround();
  glPopMatrix();
  
  disPlayer();
  glPopMatrix();
	glPushMatrix();
	drawObjects();
	glPopMatrix();
	glutSwapBuffers();
}
