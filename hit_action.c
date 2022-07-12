#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "head.h"
#include "hit.h"
#include "score.h"
#include "objects_draw.h"
#include "objects.h"

GLdouble static const cHitBoxCarrot = 1.0;
GLdouble static const cHitBoxPoisonCarrot = 1.0;
GLdouble static const cHitBoxDiamond = 1.0;
int pre_hit = 0;


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
  //printf("actionHit kidou!!\n");
  if(hit > 0){//フラグが立っているときは-1する。表示時間の調整
    hit = hit - 1;
  }
  for (int i = 0; i < sObjectCount; i++)
  {if(isHit(i)){
   //printf("%d ga hani kennnai", i);
  if( objectIsVisible(i)){//Hitしたときに立ち上がるフラグ。一定時間表示させたいので0~5の関数にしている。
    //printf("%d wo kakutoku!!\n", i);
      switch (getObjectType(i))
			{
			case CARROT:
				addScore(100);
				hit = 5;
				break;
			case P_CARROT:
				addScore(-50);
        damage();
			default:
				break;
			}
    }
    }
  }
}
