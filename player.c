#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "head.h"


GLfloat color[][4] = {
		{ 1.0, 1.0, 1.0, 1.0 },//WHITE
		{ 1.0, 0.0, 0.0, 1.0 },//RED
		{ 0.0, 1.0, 0.0, 1.0 },// GREEN
		{ 0.0, 0.0, 1.0, 1.0 },//BLUE
		{ 1.0, 1.0, 0.0, 1.0 },//YELLOW
		{ 1.0, 0.0, 1.0, 1.0 },//MAGENTA
		{ 0.0, 1.0, 1.0, 1.0 },//CYAN
		{ 0.7, 0.7, 0.7, 1.0 },//GRAY
		{ 0.0, 0.0, 0.0, 1.0 },//BLACK
    { 0.62, 0.46, 0.71, 1.0 },//PURPLE
    { 0.5, 0.4, 0.4, 1.0 },// BROWN
    { 0.99, 0.86, 0.74, 1.0 },//SKIN
   	{ 0.88, 1.0, 1.0, 1.0 },//LIGHTBLUE
		{ 0.68, 1.0, 0.18, 1.0 },//GREENYELLOW
		{ 0.69, 0.88, 0.9, 1.0 },//POWDERBLUE
		{ 1.0, 1.0, 0.2, 1.0 },//FFFF33
		{ 1.0, 0.4, 0.4, 1.0 },// FF6666
		{ 1.0, 0.98, 0.8, 1.0 }// LEMONCHIFFON 
    };//�F�𑝂₷�ꍇ�͂����ɒǉ�

//GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };//������

double L = 1;
double small_player = 0.33;//�v���C԰�̑傫����ύX
double player_w = 1.5;//�v���C���[�̉��������l��1.5(���X�̃v���C���[�I�u�W�F�N�g�̕�)

double player_x = 0;//�v���C���[�̍��Wx
double player_y = 0;//�v���C���[�̍��Wy
double player_z = 0;//�v���C���[�̍��Wz
int mySpecialValue = 0;//�v���C���[�̈ړ�����
int hit = 1;//hit�������ǂ����̃t���O

GLboolean isHit(int h){//isHit()�̂Ƃ肠�����̊֐�/�m�F�p
  if(hit == 0){
    return GL_TRUE;
  }else{
    return GL_FALSE;
    }
}
void idle(void)
{
//���E�ړ��ɏ�����������
  player_w = 1.5 * small_player;
	double MARGIN = 0.05;
  if (mySpecialValue & (1 << 0))
	{
		player_y += 0.1;
		if (depth*player_w < player_y - MARGIN)player_y -= 0.1;//�㉺�ړ�(�g��Ȃ�)
	}
	if (mySpecialValue & (1 << 1))
	{
		player_x += 0.1;
		if ((width/2.0 - player_w)*L < player_x - MARGIN)player_x -= 0.1;
	}
	if (mySpecialValue & (1 << 2))
	{
		
   player_x -= 0.1;
		if (-(width/2.0 -player_w) * L > player_x + MARGIN)player_x += 0.1;
	}
	if (mySpecialValue & (1 << 3))//�㉺�ړ�(�g��Ȃ�)
	{
		player_y -= 0.1;
		if (0 * player_w > player_y + MARGIN)player_y += 0.1;
	}
	/*
	//���_���ړ�
  glLoadIdentity();
	gluLookAt(10 + player_x, -10.0 + player_y, 5.0, 0.0 + player_x, 0.0 + player_y, 1.5, 0.0, 0.0, 1.0);
*/
  actionHit();
  //printf("%d\n", hit);//hit���쓮���Ă��邩�m�F���邽�߂̂���(���ۂ̃v���O�����ɂ͕s�v)
	glutPostRedisplay();
}
void display(void)/*�f�B�X�v���C�̕`��(���킹��ۂɑ�����������)*/
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  glPushMatrix();
  
  if(hit > 2){//hit������\������(hit��0~5�ɂ��邱�Ƃŕ\�����Ԃ̒���������)��ԍŏ��ɒu�����ق����ǂ�(�o�O�����̂�)
    printString(0.5, -0.5, "Great!!", 7);
  }
  //glPopMatrix(); 
  
  
  drawGround();
  glPopMatrix();
  
  disPlayer();
  glPopMatrix();

	glutSwapBuffers();
}

/*�~���̕`��*/
void SCone(double up, double spin1,double spin2, double mx, double my, double mz){
  glPushMatrix();
  glTranslatef(mx*small_player,my*small_player,mz*small_player);
  glRotatef(spin1,1.0,0.0,0.0);//x�����S�ɉ�]
  glRotatef(spin2,0.0,1.0,0.0);//y�����S�ɉ�]
  glScalef(up,up,up);
  glutSolidCone(1.5*small_player,3*small_player,50,30);
  glPopMatrix();
  
}
/*���̕`��*/
void Sphere(double upX, double upY, double upZ, double spin,double mx, double my, double mz){
  glPushMatrix();
  glTranslatef(mx*small_player, my*small_player, mz*small_player);
  //glRotatef(spin, 1.0, 0.0, 0.0);
  glScalef(upX, upY, upZ);
  //glScalef(1, upY, 1);
  glRotatef(spin, 1.0, 0.0, 0.0);//x�����S�ɉ�]
  glutSolidSphere(0.5*small_player, 30, 30);
  glPopMatrix();
}

/*�v���C���[�̕`��(�匳)*/
void drawPlayer(void)
{

	glPushMatrix();
	//��
	//glLightfv(GL_LIGHT0, GL_POSITION, pos_player);//�v���C���[����]����ۈꏏ�ɓ����Ĉ�a�����A������
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, color[WHITE]);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, color[WHITE]);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, color[WHITE]);
	
	//light leg
  glMaterialfv(GL_FRONT, GL_AMBIENT, color[SKIN]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[SKIN]);
	SCone(0.25,180.0,0.0,0.5,0.0,0.9);
	//left leg
	SCone(0.25,180.0,0.0,-0.5,0.0,0.9);
	//body
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[PURPLE]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[PURPLE]);
	SCone(1.0, 0.0, 0.0, 0.0, 0.0,0.9);
	//left hand
	glMaterialfv(GL_FRONT,GL_AMBIENT, color[SKIN]);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, color[SKIN]);
	SCone(0.4, 0.0, -90.0, -0.3, 0.0, 2.8);
	//light hand
	SCone(0.4, 0.0, 90.0, 0.3, 0.0, 2.8);
 
	//face
	glPushMatrix();
	glTranslatef(0.0,0.0,4.5*small_player);
	glutSolidSphere(1.2*small_player,30,30);
	glPopMatrix();
	//left eye
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLACK]);
	Sphere(0.2, 0.3, 0.8, 0.0, -0.4, -1.0, 4.5);
	//light eye
	Sphere(0.2, 0.3, 0.8, 0.0, 0.4, -1.0, 4.5);

	//Beanie
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[PURPLE]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[PURPLE]);
	SCone(0.8,-20.0, 0.0, 0.0, 0.1, 5.2);
	//Beanie ornament1��
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[WHITE]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[WHITE]);
	glPushMatrix();
	glTranslatef((-0.05)*small_player, 0.9*small_player,7.3*small_player);
	glutSolidSphere(0.5*small_player, 10, 10);
	glPopMatrix();
	//Beanie ornament2�ւ���
	glPushMatrix();
	glTranslatef((-0.05)*small_player, 0.1*small_player,5.2*small_player);
	glRotatef(-20, 1, 0, 0);
	glutSolidTorus(0.4*small_player, 1.0*small_player, 30, 30);
	glPopMatrix();
	glutSwapBuffers();
}
/*�v���C���[�̕`��(�f�B�X�v���C�\��/�}�E�X�E�L�[����ɂ��ړ���I�u�W�F�N�g�̉�])*/
void disPlayer()
{
 glPushMatrix();
 glTranslatef(player_x, player_y , player_z);//+ width / 2.0
 if (mySpecialValue & (1 << 1))
	{
		glRotatef(90, 0, 0, 1);
	}else if (mySpecialValue & (1 << 2))
	{
    glRotatef(-90, 0, 0, 1);
	}
 drawPlayer();
 glPopMatrix();
}
/*
void myTimerFunc(int value)
{
	glutTimerFunc(10, myTimerFunc, 0);
}
*/

void myKeyboardFunc(unsigned char key, int x, int y)//�W�����v�����ɂȂ�\��
{
	switch (key)
	{
	case ' ':
		break;
	}
}
void mySpcialFunc(int key, int x, int y)//�L�[�{�[�h���삻��1
{
	switch (key)
	{
 /*
	case GLUT_KEY_UP:
		mySpecialValue |= 1 << 0;//mySpecialValue��1bit�ڂ�1�ɂ���
		break;
   */
	case GLUT_KEY_LEFT:
		mySpecialValue |= 1 << 1;//mySpecialValue��2bit�ڂ�1�ɂ���(���Ɉړ�)
		break;
  case GLUT_KEY_RIGHT:
		mySpecialValue |= 1 << 2;//mySpecialValue��3bit�ڂ�1�ɂ���(�E�Ɉړ�)
		break;
	/*
  case GLUT_KEY_DOWN:
		mySpecialValue |= 1 << 3;//mySpecialValue��4bit�ڂ�1�ɂ���
		break;s
    */
	default:
		break;
	}
}
void mySpcialUpFunc(int key, int x, int y)//�L�[�{�[�h���삻��2
{
	switch (key)
	{
 /*
	case GLUT_KEY_UP:
		mySpecialValue &= ~(1 << 0);//mySpecialValue��1bit�ڂ�0�ɂ���
		break;
	*/
  case GLUT_KEY_LEFT:
		mySpecialValue &= ~(1 << 1);//mySpecialValue��2bit�ڂ�0�ɂ���(��~)
		break;
  case GLUT_KEY_RIGHT:
		mySpecialValue &= ~(1 << 2);//mySpecialValue��3bit�ڂ�0�ɂ���(��~)
		break;
   /*
	case GLUT_KEY_DOWN:
		mySpecialValue &= ~(1 << 3);//mySpecialValue��4bit�ڂ�0�ɂ���
		break;
   */
	default:
		break;
	}

}
void myMouseFunc(int button, int state, int x, int y)/*�}�E�X�̃N���b�N����(���E�ړ�)*/
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mySpecialValue |= 1 << 1;//mySpecialValue��2bit�ڂ�1�ɂ���(���Ɉړ�)
	}
 if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mySpecialValue |= 1 << 2;//mySpecialValue��3bit�ڂ�1�ɂ���(�E�Ɉړ�)
	}
 if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mySpecialValue &= ~(1 << 1);//mySpecialValue��2bit�ڂ�0�ɂ���(��~)
	}
 if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		mySpecialValue &= ~(1 << 2);//mySpecialValue��3bit�ڂ�0�ɂ���(��~)
	}
}
void myPassiveMotionFunc(int x, int y)/*�}�E�X�̍��W���擾�������(�����Ă��悢)*/
{
	//printf("(%d,%d)\n",x,y);
}

void init(void)
{
	glClearColor(0.5, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpcialFunc);
	glutSpecialUpFunc(mySpcialUpFunc);
 
  glutMouseFunc(myMouseFunc);
	glutPassiveMotionFunc(myPassiveMotionFunc);
	
  glutIdleFunc(idle);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, .1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10.0, 4.0, 0.0, -10.0, 0.0, 0.0, 0.0, 1.0);
  //gluLookAt(2.0, -10.0, 5.0, 2.0, 0.0, 1.5, 0.0, 0.0, 1.0);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color[WHITE]);
	//myTimerFunc(0);
}