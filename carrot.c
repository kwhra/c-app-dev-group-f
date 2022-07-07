#include <GL/glut.h>

GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 } ;
GLfloat orange[] = { 0.98, 0.48, 0.0, 1.0 };
GLfloat purple[] = { 0.75, 0.19, 0.75, 1.0 };

void drawCarrot(void)
{
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
	glutSolidCone(0.5, 1.8, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glTranslatef(0, 0, -0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glutSolidCone(0.25, 1.2, 20, 20);
	glPopMatrix();

}

void drawPoisonCarrot(void)
{
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
	glutSolidCone(0.5, 1.8, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glTranslatef(0, 0, -0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glutSolidCone(0.25, 1.2, 20, 20);
	glPopMatrix();
}
