#include <GL/glut.h>
#include <stdio.h>
// time left (msec)
int static sTimeLeft = 1;
int getTimeLeft(){
	return sTimeLeft;
}
void setTimeLeft(int msec){
	sTimeLeft = msec;
}
void declineTimeLeft(int msec){
	sTimeLeft -= msec;
}
GLboolean isTimeUp(){
	if(sTimeLeft <= 0){
		return GL_TRUE;
	}else{
		return GL_FALSE;
	}
}