#include <stdio.h>

void merge(int *A, int p, int q, int r){
	int i, j;
	int n1=q-p+1;
	int n2=r-q;
	int L[n1];
	int R[n2];
	for(i=0;i<n1;i++)
		L[i]=A[p+i];
	for(j=0;j<n2;j++)
		R[j]=A[q+j+1];
	j=0;
	i=0;
	int k=p;
	while(i<n1 && j<n2){
		if(L[i]<=R[j]){
			A[k]=L[i];
			i++;
		} else {
			A[k]=R[j];
			j++;
		}
		k++;
	}
	while(i<n1){
		A[k]=L[i];
		i++;
		k++;
	}
	while(j<n2){
		A[k]=R[j];
		j++;
		k++;
	}
}

void sort(int *A, int p, int r){
	//p левая граница, r правая граница
	if(p<r){
		int q=(r+p)/2;
		sort(A, p, q);
		sort(A, q+1, r);
		merge(A, p, q, r);		
	}
}

int main(){
	int n, i;
	FILE* in=fopen("sort.in","r");
	FILE* out=fopen("sort.out","w");
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





















