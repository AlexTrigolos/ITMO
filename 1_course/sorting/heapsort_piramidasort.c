#include <stdio.h>

void sift_down(int *A, int i, int n){
	int l = 2 * i;
	int r = 2 * i + 1;
	int index;
	int per;
	if(l <= n && A[i] < A[l]){
		index = l;
	} else {
		index = i;
	}
	if(r <= n && A[index] < A[r]){
		index = r;
	}
	if(index != i){
		per = A[i];
		A[i] = A[index];
		A[index] = per;
		sift_down(A, index, n);
	}
}

int main(){
	int n, i, size;
	FILE* in=fopen("sort.in","r");
	FILE* out=fopen("sort.out","w");
	fscanf(in, "%d", &n);
	int A[n];
	for(i=1;i<=n;++i){
		fscanf(in, "%d", &A[i]);
	}
	size=n;
	for(i=size/2; i>0; i--){
		sift_down(A, i, n);
	}
	size = n;
	while(size > 0){
		int per = A[size];
		A[size] = A[1];
		A[1] = per;
		size--;
		sift_down(A, 1, size);
	}
	for(i=1; i<=n; i++){
		fprintf(out, "%d ", A[i]);
	}
	fclose(in);
	fclose(out);
	return 0;
}