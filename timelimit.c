#include <GL/glut.h>
#include <stdio.h>
int static sTimeLimit = 1;
int getTimeLimit(){
	return sTimeLimit;
}
void setTimeLimit(int tl){
	sTimeLimit = tl;
}
void declineTimeLimit(){
	sTimeLimit -= 1;
}
GLboolean isTimeUp(){
	if(sTimeLimit == 0){
		return GL_TRUE;
	}else{
		return GL_FALSE;
	}
}