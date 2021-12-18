#include <stdio.h>

int main(){
	int i, n, m=0;
	FILE* in = fopen("isheap.in","r");
	FILE* out = fopen("isheap.out","w");
	fscanf(in, "%d", &n);
	long int A[n];
	for(i = 1; i <=n; ++i){
		fscanf(in, "%d", &A[i]);
	}
	i=1;
	while(2*i<=n){
		if(A[i]>A[2*i]){
			m++;
		}
		++i;
	}
	i=1;
	while(2*i+1<=n){
		if(A[i]>A[2*i+1]){
			m++;
		}
		++i;
	}
	if(m>0){
		fprintf(out, "NO");
	} else {
		fprintf(out, "YES");
	}
	fclose(in);
	fclose(out);
	return 0;
}