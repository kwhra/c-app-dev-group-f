#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "head.h"

void printString(float x, float y, char* str, int length){//文字を出力する関数
  int i, j;
	float z = -1.0f;
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(0.0, 0.0, 0.0);
	
	glRasterPos3f(x, y, z);
	for (i = 0; i < length; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}
void actionHit(){
  if(hit > 0){//フラグが立っているときは-1する。表示時間の調整
    hit = hit - 1;
  }
  if(isHit(hit)){//Hitしたときに立ち上がるフラグ。一定時間表示させたいので0~5の関数にしている。
    hit = 5;
  }
}
