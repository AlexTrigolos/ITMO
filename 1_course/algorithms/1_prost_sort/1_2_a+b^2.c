#include <stdio.h>

int main(){
	int a, b;
	FILE *f=fopen("aplusbb.in","r");
	fscanf(f, "%lli%lli", &a, &b);
	fclose(f);
	FILE *o=fopen("aplusbb.out","w");
	fprintf(o, "%lli", a+(b*b));
	fclose(o);
	return 0;
}