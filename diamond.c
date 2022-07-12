#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "diamond.h"

#ifndef M_PI
#define M_PI 3.14159265358978323846 
#endif

/* count */
#define DEMENSION 3
#define OCT 13
#define LEVEL 4

/* diamond size */
#define R_TOP 0.7
#define R_MID 1.2
#define R_BOTTOM 0.3
#define H_TOP 0.7
#define H_MID 0.1
#define H_BOTTOM 1.5

/* ring size */
#define R_INNER 0.2
#define R_OUTER 2

/* light color */
#define LIGHT_DIF 0.6
#define LIGHT_AMB 0.2
#define LIGHT_SPEC 0.6

/* diamond material color */
GLfloat static diamond_ambient[] = { 0.7, 0.7, 0.7, 1 };
GLfloat static diamond_diffuse[] = { 0.7, 0.7, 0.7, 1 };
GLfloat static diamond_specular[] = { 0.7, 0.7, 0.7, 1 };
GLfloat static diamond_shininess = 30;
GLfloat static diamond_emission[] = { 0.07, 0.07, 0.3, 1 };

/* diamond material color */
GLfloat static ring_ambient[] = { 0.24725, 0.1995, 0.0745, 1 };
GLfloat static ring_diffuse[] = { 0.75164, 0.60648, 0.22648, 1 };
GLfloat static ring_specular[] = { 0.628281, 0.555802, 0.366065, 1 };
GLfloat static ring_shininess = 48;
GLfloat static ring_emission[] = { 0.1, 0.1, 0.1, 1 };

/*light color*/
GLfloat static light_position[] = { -5.0, 0.0, 5.0, 0.0 };
GLfloat static light_direction[] = { 1, 0, -1, 0 };
GLfloat static light_diffuse[] = { LIGHT_DIF, LIGHT_DIF, LIGHT_DIF, 1.0 };
GLfloat static light_ambient[] = { LIGHT_AMB, LIGHT_AMB, LIGHT_AMB,  1.0 };
GLfloat static light_specular[] = { LIGHT_SPEC, LIGHT_SPEC, LIGHT_SPEC, 1.0 };


GLdouble static vertex[LEVEL][OCT][DEMENSION];
GLdouble static radius[LEVEL] = {R_TOP, R_MID, R_MID, R_BOTTOM};
GLdouble static hight[LEVEL] = {H_TOP, H_MID, -1*H_MID, -1*H_BOTTOM};

void init_vertex() {
	int i, j;
	for ( i = 0; i < LEVEL; i++) {
		for ( j = 0; j < OCT; j++) {
			vertex[i][j][0] = radius[i] * cos(j * 2 * M_PI / OCT);
			vertex[i][j][1] = radius[i] * sin(j * 2 * M_PI / OCT);
			vertex[i][j][2] = hight[i];
		}
	}
}

GLdouble static norm_vec[DEMENSION] = {0.0, 0.0, 0.0};

GLdouble* norm(GLdouble* a, GLdouble* b, GLdouble* c) {
	GLdouble vec1[DEMENSION], vec2[DEMENSION];
	int k;
	for (k = 0; k < DEMENSION; k++) {
		vec1[k] = b[k] - a[k];
		vec2[k] = c[k] - a[k];
	}
	GLdouble len_vec = 0.0;
	for (k = 0; k < DEMENSION; k++) {
		int i = (k + 1) % DEMENSION;
		int j = (k + 2) % DEMENSION;
		norm_vec[k] = vec1[i] * vec2[j] - vec1[j] * vec2[i];
		len_vec += norm_vec[k] * norm_vec[k];
	}
	for ( k = 0; k < DEMENSION; k++) {
		norm_vec[k] /= sqrt(len_vec);
	}
	return norm_vec;
}

void static octagon() {
	int j;
	/* top */
	glBegin(GL_POLYGON);
	glNormal3dv(norm(vertex[0][0], vertex[0][1], vertex[0][2]));
	for (j = 0; j < OCT; j++) {
		glVertex3dv(vertex[0][j]);
	}
	glEnd();
	/* bottom */
	glBegin(GL_POLYGON);
	glNormal3dv(norm(vertex[3][0], vertex[3][1], vertex[3][2]));
	/* reverse */
	for (j = 0; j < OCT; j++) {
		glVertex3dv(vertex[0][OCT-j-1]);
	}
	glEnd();
}

void static squads() {
	int i, j;
	glBegin(GL_QUADS);
	for ( i = 0; i < LEVEL-1; i++) {
		for ( j = 0; j < OCT; j++) {
			GLdouble* a = vertex[i][j];
			GLdouble* b = vertex[i+1][j];
			GLdouble* c = vertex[i+1][(j+1) % OCT];
			GLdouble* d = vertex[i][(j+1) % OCT];
			glNormal3dv(norm(a, b, c));
			glVertex3dv(a);
			glVertex3dv(b);
			glVertex3dv(c);
			glVertex3dv(d);
		}
	}
	glEnd();
}

void static diamond() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diamond_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diamond_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, diamond_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, diamond_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, diamond_emission);
	octagon();
	squads();
}

void static ring() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ring_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ring_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ring_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ring_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ring_emission);
	glutSolidTorus(R_INNER, R_OUTER, 8, 16);
}

void static diamondring() {
	glPushMatrix();
	glScaled(0.3, 0.3, 0.3);
	glTranslated(0, 0, H_BOTTOM+R_OUTER);
	diamond();
	glTranslated(0, 0, -H_BOTTOM - R_OUTER);
	glRotatef(90, 1, 0, 0);
	ring();
	glPopMatrix();
}

GLboolean static isInitialized = GL_FALSE;

void static init()
{
	if (isInitialized){
		// do nothing
	}else{
		isInitialized = GL_TRUE;
		init_vertex();
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
}

void drawDiamond()
{
	init();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	diamondring();
	glPopMatrix();
	glutSwapBuffers();
}

