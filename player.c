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
    };//色を増やす場合はここに追加

//GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };//消した

double L = 1;
double small_player = 0.33;//プレイﾔｰの大きさを変更
double player_w = 1.5;//プレイヤーの横幅初期値は1.5(元々のプレイヤーオブジェクトの幅)

double player_x = 0;//プレイヤーの座標x
double player_y = 0;//プレイヤーの座標y
double player_z = 0;//プレイヤーの座標z
int mySpecialValue = 0;//プレイヤーの移動判定
int hit = 1;//hitしたかどうかのフラグ

GLboolean isHit(int h){//isHit()のとりあえずの関数/確認用
  if(hit == 0){
    return GL_TRUE;
  }else{
    return GL_FALSE;
    }
}
void idle(void)
{
//左右移動に上限をつけるもの
  player_w = 1.5 * small_player;
	double MARGIN = 0.05;
  if (mySpecialValue & (1 << 0))
	{
		player_y += 0.1;
		if (depth*player_w < player_y - MARGIN)player_y -= 0.1;//上下移動(使わない)
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
	if (mySpecialValue & (1 << 3))//上下移動(使わない)
	{
		player_y -= 0.1;
		if (0 * player_w > player_y + MARGIN)player_y += 0.1;
	}
	/*
	//視点を移動
  glLoadIdentity();
	gluLookAt(10 + player_x, -10.0 + player_y, 5.0, 0.0 + player_x, 0.0 + player_y, 1.5, 0.0, 0.0, 1.0);
*/
  actionHit();
  //printf("%d\n", hit);//hitが作動しているか確認するためのもの(実際のプログラムには不要)
	glutPostRedisplay();
}
void display(void)/*ディスプレイの描画(合わせる際に多分消すもの)*/
{
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

	glutSwapBuffers();
}

/*円錐の描画*/
void SCone(double up, double spin1,double spin2, double mx, double my, double mz){
  glPushMatrix();
  glTranslatef(mx*small_player,my*small_player,mz*small_player);
  glRotatef(spin1,1.0,0.0,0.0);//x軸中心に回転
  glRotatef(spin2,0.0,1.0,0.0);//y軸中心に回転
  glScalef(up,up,up);
  glutSolidCone(1.5*small_player,3*small_player,50,30);
  glPopMatrix();
  
}
/*球の描画*/
void Sphere(double upX, double upY, double upZ, double spin,double mx, double my, double mz){
  glPushMatrix();
  glTranslatef(mx*small_player, my*small_player, mz*small_player);
  //glRotatef(spin, 1.0, 0.0, 0.0);
  glScalef(upX, upY, upZ);
  //glScalef(1, upY, 1);
  glRotatef(spin, 1.0, 0.0, 0.0);//x軸中心に回転
  glutSolidSphere(0.5*small_player, 30, 30);
  glPopMatrix();
}

/*プレイヤーの描画(大元)*/
void drawPlayer(void)
{

	glPushMatrix();
	//光
	//glLightfv(GL_LIGHT0, GL_POSITION, pos_player);//プレイヤーを回転する際一緒に動いて違和感が、消した
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
	//Beanie ornament1玉
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[WHITE]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[WHITE]);
	glPushMatrix();
	glTranslatef((-0.05)*small_player, 0.9*small_player,7.3*small_player);
	glutSolidSphere(0.5*small_player, 10, 10);
	glPopMatrix();
	//Beanie ornament2輪っか
	glPushMatrix();
	glTranslatef((-0.05)*small_player, 0.1*small_player,5.2*small_player);
	glRotatef(-20, 1, 0, 0);
	glutSolidTorus(0.4*small_player, 1.0*small_player, 30, 30);
	glPopMatrix();
	glutSwapBuffers();
}
/*プレイヤーの描画(ディスプレイ表示/マウス・キー操作による移動やオブジェクトの回転)*/
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

void myKeyboardFunc(unsigned char key, int x, int y)//ジャンプ処理になる予定
{
	switch (key)
	{
	case ' ':
		break;
	}
}
void mySpcialFunc(int key, int x, int y)//キーボード操作その1
{
	switch (key)
	{
 /*
	case GLUT_KEY_UP:
		mySpecialValue |= 1 << 0;//mySpecialValueの1bit目を1にする
		break;
   */
	case GLUT_KEY_LEFT:
		mySpecialValue |= 1 << 1;//mySpecialValueの2bit目を1にする(左に移動)
		break;
  case GLUT_KEY_RIGHT:
		mySpecialValue |= 1 << 2;//mySpecialValueの3bit目を1にする(右に移動)
		break;
	/*
  case GLUT_KEY_DOWN:
		mySpecialValue |= 1 << 3;//mySpecialValueの4bit目を1にする
		break;s
    */
	default:
		break;
	}
}
void mySpcialUpFunc(int key, int x, int y)//キーボード操作その2
{
	switch (key)
	{
 /*
	case GLUT_KEY_UP:
		mySpecialValue &= ~(1 << 0);//mySpecialValueの1bit目を0にする
		break;
	*/
  case GLUT_KEY_LEFT:
		mySpecialValue &= ~(1 << 1);//mySpecialValueの2bit目を0にする(停止)
		break;
  case GLUT_KEY_RIGHT:
		mySpecialValue &= ~(1 << 2);//mySpecialValueの3bit目を0にする(停止)
		break;
   /*
	case GLUT_KEY_DOWN:
		mySpecialValue &= ~(1 << 3);//mySpecialValueの4bit目を0にする
		break;
   */
	default:
		break;
	}

}
void myMouseFunc(int button, int state, int x, int y)/*マウスのクリック操作(左右移動)*/
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mySpecialValue |= 1 << 1;//mySpecialValueの2bit目を1にする(左に移動)
	}
 if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mySpecialValue |= 1 << 2;//mySpecialValueの3bit目を1にする(右に移動)
	}
 if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mySpecialValue &= ~(1 << 1);//mySpecialValueの2bit目を0にする(停止)
	}
 if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		mySpecialValue &= ~(1 << 2);//mySpecialValueの3bit目を0にする(停止)
	}
}
void myPassiveMotionFunc(int x, int y)/*マウスの座標を取得するもの(消してもよい)*/
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