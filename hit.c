#include <math.h>
#include <GL/glut.h>
#include "hit.h"
#include "object_location.h"

// let 0 is player
// if hit with argument object, true
GLboolean isHit(int object){
	GLdouble playerLocation = getObjcetLocation(0);
	GLdouble objectLocation = getObjcetLocation(object);
	GLdouble distance = fabs(playerLocation - objectLocation);
	GLdouble playerHitBox = getObjectHitBox(0);
	GLdouble objectHitBox = getObjectHitBox(object);
	GLdouble hitReach = playerHitBox + objectHitBox;
	//dits < hitReach then hit
	//  ---        ------- hit box
	//   o <--dist--> o             => not hit
	//
	//  ---------- hit box
	//   o<-->o                     =>  hit
	
	if (distance < hitReach) {
		return GL_TRUE;
	}else{
		return GL_FALSE;
	}
}