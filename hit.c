#include <math.h>
#include <GL/glut.h>
#include "hit.h"
#include "objects.h"

// let 0 is player
// if hit with argument object, true
GLboolean isHit(int index){
	GLdouble playerLocation = getObjectX(ME);
	GLdouble objectLocation = getObjectX(index);
	GLdouble distance = fabs(playerLocation - objectLocation);
	GLdouble playerHitBox = getObjectHitBox(ME);
	GLdouble objectHitBox = getObjectHitBox();
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