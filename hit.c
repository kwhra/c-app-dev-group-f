#include <math.h>
#include <GL/glut.h>
#include "hit.h"
#include "objects.h"
#include "head.h"

GLdouble static const cHitBoxCarrot = 1.0;
GLdouble static const cHitBoxPoisonCarrot = 1.0;
GLdouble static const cHitBoxDiamond = 1.0;

GLdouble getObjectHitBox(int index){
	switch (getObjectType(index))
	{
	case CARROT:
		return cHitBoxCarrot;
		break;
	case P_CARROT:
		return cHitBoxPoisonCarrot;
	case DIAMOND:
		return cHitBoxDiamond;
	default:
		return 0.0;
		break;
	}
}

// if hit with argument object, true
GLboolean isHit(int index){
	GLdouble playerLocation = player_x;
	GLdouble objectLocation = getObjectX(index);
	GLdouble distance = fabs(playerLocation - objectLocation);
	GLdouble playerHitBox = getObjectHitBox(ME);
	GLdouble objectHitBox = getObjectHitBox(index);
	GLdouble hitReach = playerHitBox + objectHitBox;
	//dits < hitReach then hit
	//  ---        ------- hit box
	//   o <--dist--> o             => not hit
	//
	//  ---------- hit box
	//   o<-->o                     =>  hit
	
	if (getObjectY(index) > -2.0 && distance < hitReach-0.7) {
		return GL_TRUE;
	}else{
		return GL_FALSE;
	}
}