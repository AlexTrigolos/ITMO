#include <stdio.h>

void merge(int *A, int p, int q, int r, long long int *m){
	int i, j;
	int n1=q-p+1;
	int n2=r-q;
	int L[n1];
	int R[n2];
	for(i=0;i<n1;i++){
		L[i]=A[p+i];
	}
	for(j=0;j<n2;j++){
		R[j]=A[q+j+1];
	}
	j=0;
	i=0;
	int k=p;
	while(i<n1 && j<n2){
		if(L[i]<=R[j]){
			A[k]=L[i];
			i++;
			*m = *m + j;
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
		*m = *m + j;
	}
	while(j<n2){
		A[k]=R[j];
		j++;
		k++;
	}
}

void sort(int *A, int p, int r, long long int *m){
	if(p<r){
		int q=(r+p)/2;
		sort(A, p, q, m);
		sort(A, q+1, r, m);
		merge(A, p, q, r, m);		
	}
}

int main(){
	int n, i;
	long long int m=0;
	FILE* in=fopen("inversions.in","r");
	FILE* out=fopen("inversions.out","w");
	fscanf(in, "%d", &n);
	int A[n];
	for(i=0;i<n;++i){
		fscanf(in, "%d", &A[i]);
	}
	sort(A, 0, n-1, &m);
	fprintf(out, "%lli", m);
	fclose(in);
	fclose(out);
	return 0;
}





















