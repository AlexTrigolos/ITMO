#include <stdio.h>

int main(){
	int n, i, j, k;
	FILE *f=fopen("smallsort.in","r");
	fscanf(f, "%d", &n);
	int Arr[n];
	for(i=0;i<n;i++){
		fscanf(f, "%d", &Arr[i]);
	}
	fclose(f);
	for(i=1;i<n;i++){
		k=Arr[i];
		j=i-1;
		while(k<Arr[j] && j>=0){
			Arr[j+1]=Arr[j];
			j--;
		}
		Arr[j+1]=k;
	}
	FILE *o=fopen("smallsort.out","w");
	for(i=0;i<n-1;i++){
		fprintf(o, "%d ", Arr[i]);
	}
	fprintf(o, "%d", Arr[n-1]);
	fclose(o);
	return 0;
}
