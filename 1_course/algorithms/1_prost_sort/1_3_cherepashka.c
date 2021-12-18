#include <stdio.h>

int main(){
	int h, w, i, j;
	FILE *f=fopen("turtle.in","r");
	fscanf(f, "%d%d", &h, &w);
	int Arr[h+1][w+1];
	for(i=0;i<=h;i++){
		for(j=0;j<=w;j++){
			if(i!=h && j!=0)
				fscanf(f, "%d", &Arr[i][j]);
			else Arr[i][j]=0;
		}
	}
	fclose(f);
	for(i=h-1;i>=0;i--){
		for(j=1;j<=w;j++){
			if(Arr[i+1][j]>=Arr[i][j-1])
				Arr[i][j]+=Arr[i+1][j];
			else Arr[i][j]+=Arr[i][j-1];
		}
	}
	FILE *o=fopen("turtle.out","w");
	fprintf(o, "%d", Arr[0][w]);
	fclose(o);
	return 0;
}