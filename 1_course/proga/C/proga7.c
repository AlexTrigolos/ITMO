#include <stdio.h>
#include <math.h>

enum music{
	classic=1,
	pop,
	rok=12,
	rep,
	newadj,
	electro,
	td
};

struct triangle{
	int ax;
	int ay;
	int bx;
	int by;
	int cx;
	int cy;
	int ab;
	int ac;
	int s;
};

union status{
	struct{
		unsigned rec : 1;
		unsigned pause : 1;
		unsigned play : 1;
	}bits;
};

int main(){
	//enum
	enum music a, b, c, d, e, f, g;
	a = classic;
	b = pop;
	c = rok;
	d = rep;
	e = newadj;
	f = electro;
	g = td;
	printf("rok = %d\n", c);
	
	//struct triangle
	struct triangle first = {1, 1, 3, 1, 1, 3, first.ax - first.bx, first.ay - first.cy, (first.ay - first.cy)*(first.ax - first.bx)/2};
	printf("S = %d\n", first.s);
	
	//union struct 
	union status mystatus;
	scanf("%x", &(mystatus.bits));
	printf("rec : %s\n", (mystatus.bits.rec) ? "on" : "off");
	printf("pause : %s\n", (mystatus.bits.pause) ? "on" : "off");
	printf("play : %s\n", (mystatus.bits.play ) ? "on" : "off");
	return 0;
}