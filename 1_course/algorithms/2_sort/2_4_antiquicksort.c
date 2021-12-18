#include <stdio.h>

int main(){
	int n, i, b;
	FILE* in=fopen("antiqs.in","r");
	FILE* out=fopen("antiqs.out","w");
	fscanf(in, "%d", &n);
	int A[n];
	for(i=0;i<n;i++){
		A[i]=i+1;
	}
	for(i=0;i<n;i++){
		b=A[i];
		A[i]=A[i/2];
		A[i/2]=b;
	}
	for(i=0;i<n;i++){
		fprintf(out, "%d ", A[i]);
	}
	fclose(in);
	fclose(out);
	return 0;
}
