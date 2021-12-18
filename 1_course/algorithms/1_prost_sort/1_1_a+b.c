#include <stdio.h>

int main(){
	int a, b;
	FILE *f=fopen("aplusb.in","r");
	fscanf(f, "%d%d", &a, &b);
	fclose(f);
	FILE *o=fopen("aplusb.out","w");
	fprintf(o, "%d", a+b);
	fclose(o);
	return 0;
}

