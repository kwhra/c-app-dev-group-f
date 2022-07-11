#include <GL/glut.h>
#include <math.h>
#include "score.h"
#include "head.h"
#include <stdio.h>
#include "result.h"

#define GREAT 4 //良い結果の条件
#define EXCELLENT 9 //とても良い結果の条件
#define CIRCLE_N 30 //2Dの〇の描画(正何角形を)
#define FACE_N 100 //顔の線の描画
#define PI2 (3.1415*2)//π*2
#define D_z -1.0f//二次元での描画のときのZ座標(2D_zの2を抜いた)。ずらすと映らないときがある。
int kakunin = 1;//確認用

/*void printString(float x, float y, char* str, int length){
	float z = -1.0f;
	glRasterPos3f(x, y, z);
	
	for (int i = 0; i < length; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}*/
void displayPlayer2D(void){//プレイヤーオブジェクトの描画(結果画面用)
  glColor3d(1.0, 1.0, 1.0);
  //帽子の表示
  glBegin(GL_POLYGON);
  glVertex3d(0.25, -0.35, D_z);
  glVertex3d(0.8, -0.45, D_z);
  glVertex3d(0.75, 0.0, D_z);
  glVertex3d(0.5, 0.0, D_z);  
  glEnd();
  //帽子の玉の表示
  glBegin(GL_POLYGON);
  for (int i = 0; i < CIRCLE_N;i++)
    glVertex3d(0.75+cos(PI2*i/CIRCLE_N)/10, 0.0+sin(PI2*i/CIRCLE_N)/10,  D_z);
  glEnd();
  //左目の表示
  glBegin(GL_POLYGON);
  for (int i = 0; i < CIRCLE_N;i++)
    glVertex3d(0.5+cos(PI2*i/CIRCLE_N)/40, -0.5+sin(PI2*i/CIRCLE_N)/20,  D_z);
  glEnd();
  //右目の表示
  glBegin(GL_POLYGON);
  for (int i = 0; i < CIRCLE_N;i++)
    glVertex3d(0.3+cos(PI2*i/CIRCLE_N)/40, -0.5+sin(PI2*i/CIRCLE_N)/20,  D_z);
  glEnd();
  //口の表示
  for(int j = 0; j < FACE_N/2; j++){
  glBegin(GL_POLYGON);
    for (int i = 0; i < CIRCLE_N;i++)
      glVertex3d(0.4-0.05*cos(PI2*j/FACE_N)+cos(PI2*i/CIRCLE_N)/50, -0.63-0.04*sin(PI2*j/FACE_N)+sin(PI2*i/CIRCLE_N)/50, D_z);
  glEnd();
  }
  //輪郭の表示
  for(int j = 0; j < FACE_N; j++){
  if(j< FACE_N*8/13 || j > FACE_N*3/4){
    glBegin(GL_POLYGON);
    for (int i = 0; i < CIRCLE_N;i++)    
      glVertex3d(0.5+0.3*cos(PI2*j/FACE_N)+cos(PI2*i/CIRCLE_N)/50, -0.5+0.3*sin(PI2*j/FACE_N)+sin(PI2*i/CIRCLE_N)/50, D_z);
  }
  glEnd();
  }
  //右手の表示
  for(int j = 0; j < FACE_N; j++){
  glBegin(GL_POLYGON);
    for (int i = 0; i < CIRCLE_N;i++)    
      glVertex3d(0.3+0.08*cos(PI2*j/FACE_N)+cos(PI2*i/CIRCLE_N)/50, -0.9+0.2*sin(PI2*j/FACE_N)+sin(PI2*i/CIRCLE_N)/50, D_z);
  glEnd();
  }  
  //左手の表示
  for(int j = 0; j < FACE_N; j++){
  glBegin(GL_POLYGON);
    for (int i = 0; i < CIRCLE_N;i++)
      glVertex3d(0.7+0.2*cos(PI2*j/FACE_N)+cos(PI2*i/CIRCLE_N)/50, -0.85+0.08*sin(PI2*j/FACE_N)+sin(PI2*i/CIRCLE_N)/50, D_z);
  glEnd();
  }  
  //胴体の表示
  glBegin(GL_POLYGON);
  glVertex3d(0.35, -1.0, D_z);
  glVertex3d(0.8, -1.0, D_z);
  glVertex3d(0.65, -0.75, D_z);
  glVertex3d(0.35, -0.75, D_z);  
  glEnd();
}
void displayResult(void)
{
	int i,j, score_1digit;
  int score_digit = 0;
  
	glClear(GL_COLOR_BUFFER_BIT);

	//game screan
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	int score = getScore();
	glColor3d(1.0, 1.0, 1.0);
 
  printString(-0.8, 0.7, "Result",6);
   printString(-0.8, 0, "Score", 5);
   //スコアを一桁ずつ格納する。
   if(score > EXCELLENT){
     printString(-0.55 , -0.3, "EXCELLENT!!", 11);
   }else if(score > GREAT){
     printString(-0.3, -0.3, "GREAT!!", 7);
   }else{
     printString(-0.50 , -0.3, "GOOD JOB!!", 10);
   }
   
   for(i = 1;;i++){   
     if(score != 0){
       score_1digit = score % 10;//スコアの最下位桁の数字を取り出す
       /*if(kakunin > 0){
       printf("%d / (%d)\n",score, 10);//確認用プログラム
       }*/
       char char_score= score_1digit + '0';
       char* char_score2 = &char_score;//ポインタ変数に変換
       printString(0.3 - 0.1*i, 0, char_score2, 1);//描画
       /*if(kakunin > 0){
       printf("%dを%dに格納した\n",score_1digit, i);//確認用プログラム
       }*/
       score = score / 10;//スコアの最下位桁を削除
       /*if(kakunin>0){
       printf("スコアは%dに\n",score);//確認用プログラム
       }*/
     }else{
     /*
     if(kakunin > 0){
     printf("やったよ\n");//確認用プログラム
     kakunin = -1;
     }*/
     break;//処理が終わったらループから抜け出す
     }
   }
   
   
   for (i = 0; i < 6; i++) {//Resultの左横の棒の描画
	   printString(-0.98 + 0.02 * i, 0.7, "-", 1);

   }
   for (i = 0; i < 70; i++) {//Resultの右横の描画
	   printString(-0.4+ 0.02* i, 0.7, "-", 1);
   }
   for (i = 0; i < 50; i++) {
	   printString(-0.98 + 0.02 * i, -0.7, "-", 1);

   }
   for(i=0;i<32;i++){
   printString(-0.98, 0.62-0.04*i, "|", 1);
   
   }
   for (i = 0; i < 32; i++) {
	   printString(0.96, 0.62 - 0.04 * i, "|", 1);

   }
   displayPlayer2D();
	glutSwapBuffers();
}
