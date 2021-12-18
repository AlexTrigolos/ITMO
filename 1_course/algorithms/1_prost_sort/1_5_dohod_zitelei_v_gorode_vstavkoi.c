#include <stdio.h>

int main(){
	int n, i, j, k, k1;
	FILE *f=fopen("sortland.in","r");
	fscanf(f, "%d", &n);
	float Arr[n];
	int A[n];
	for(i=1;i<=n;i++){
		fscanf(f, "%f", &Arr[i]);
		A[i]=i;
	}
	fclose(f);
	for(i=2;i<=n;i++){
		k=Arr[i];
		k1=A[i];
		j=i-1;
		while(k<Arr[j] && j>=1){
			Arr[j+1]=Arr[j];
			A[j+1]=A[j];
			j--;
		}
		Arr[j+1]=k;
		A[j+1]=k1;
	}
	FILE *o=fopen("sortland.out","w");
	fprintf(o, "%d %d %d", A[1], A[(n+1)/2], A[n]);
	fclose(o);
	return 0;
}