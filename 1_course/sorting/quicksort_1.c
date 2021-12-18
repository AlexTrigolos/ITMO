#include <stdio.h>

int partition(int* A, int p, int r){
	int pivot=A[(r+p)/2], o;
	int i=p;
	int j=r;
	while(p<=r){
		while(A[i] < pivot)
			i++;
		while(A[j] > pivot)
			j--;
		if(i>=j){
			break;
		}
		o=A[i];
		A[i]=A[j];
		A[j]=o;
		if(A[i]==A[j]){
			i++;
			j--;
		}
	}
	return j;
}

void sort(int* A, int p, int r){
	if(p<r){
		int q=partition(A, p, r);
		sort(A, p, q-1);
		sort(A, q+1, r);
	}
}

int main(){
	int n, i;
	FILE* in=fopen("race.in","r");
	FILE* out=fopen("race.out","w");
	fscanf(in, "%d", &n);
	int A[n];
	for(i=0;i<n;++i){
		fscanf(in, "%d", &A[i]);
	}
	sort(A, 0, n-1);
	for(i=0; i<n; i++){
		fprintf(out, "%d ", A[i]);
	}
	fclose(in);
	fclose(out);
	return 0;
}