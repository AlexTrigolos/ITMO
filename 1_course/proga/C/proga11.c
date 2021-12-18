#include <stdio.h>
#include "proga11_1.c"

struct rombik{
	float x1, x2, x3, x4 ,y1, y2, y3, y4;
};

int main(){
	printf("ROMB\nROMB\nROMB\nINPUT:\nA = x y\nB = x y\nC = x y\nD = x y\n");
	struct rombik romb;
	scanf("%f %f %f %f %f %f %f %f", &romb.x1, &romb.y1, &romb.x2, &romb.y2, &romb.x3, &romb.y3, &romb.x4, &romb.y4);
	P(romb.x1, romb.y1, romb.x2, romb.y2);
	S(romb.x1, romb.y1, romb.x2, romb.y2, romb.x3, romb.y3, romb.x4, romb.y4);
	return 0;
}