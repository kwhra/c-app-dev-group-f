#include "score.h"
static int sScore = 0;
int getScore(){
	return sScore;
}
void setScore(int score){
	sScore = score;
}
void addScore(int points){
	sScore += points;
}