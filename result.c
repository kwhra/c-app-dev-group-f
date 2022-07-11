#include <GL/glut.h>
#include "score.h"

static void printString(float x, float y, char* str, int length){
	float z = -1.0f;
	glRasterPos3f(x, y, z);
	
	for (int i = 0; i < length; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}

void displayResult(void)
{
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//game screan
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	int score = getScore();
	glColor3d(1.0, 1.0, 1.0);
   char char_score= score + '0';
   char* char_score2 = &char_score;
   printString(-0.8, 0.7, "Result",6);
   printString(-0.8, 0, "Score", 5);
   printString(0.1, 0, char_score2, 1);
   for (i = 0; i < 6; i++) {
	   printString(-0.98 + 0.02 * i, 0.7, "-", 1);

   }
   for (i = 0; i < 70; i++) {
	   printString(-0.4+ 0.02* i, 0.7, "-", 1);
   }
   for (i = 0; i < 99; i++) {
	   printString(-0.98 + 0.02 * i, -0.7, "-", 1);

   }
   for(i=0;i<32;i++){
   printString(-0.98, 0.62-0.04*i, "|", 1);
   
   }
   for (i = 0; i < 32; i++) {
	   printString(1.03, 0.62 - 0.04 * i, "|", 1);

   }
	 glPopMatrix();
	glutSwapBuffers();
}
