#ifndef PROGA11_1_C
#define PROGA11_1_C
#include <stdio.h>
#include <math.h>


void P(float x1, float y1, float x2, float y2){
printf("%.1f\n", 4 * sqrt(pow(abs((int)(x1 - x2)), 2) + pow(abs((int)(y1 - y2)), 2)));
}

void S(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	printf("%.1f\n", sqrt(pow(abs((int)(x1 - x3)), 2) + pow(abs((int)(y1 - y3)), 2)) * sqrt(pow(abs((int)(x2 - x4)), 2) + pow(abs((int)(y2 - y4)), 2)) * 0.5);
}

#endif