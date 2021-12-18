#include <stdio.h>

void merge(int *U, int p, int q, int r){
	int i, j, n1=q-p+1, n2=r-q, L[n1], R[n2], k=p;
	for(i=0;i<n1;i++)
		L[i]=U[p+i];
	for(j=0;j<n2;j++)
		R[j]=U[q+j+1];
	j=0;
	i=0;
	while(i<n1 && j<n2){
		if(L[i]<=R[j]){
			U[k]=L[i];
			i++;
		} else {
			U[k]=R[j];
			j++;
		}
		k++;
	}
	while(i<n1){
		U[k]=L[i];
		i++;
		k++;
	}
	while(j<n2){
		U[k]=R[j];
		j++;
		k++;
	}
}

void sort(int *U, int p, int r){
	if(p<r){
		int q=(r+p)/2;
		sort(U, p, q);
		sort(U, q+1, r);
		merge(U, p, q, r);		
	}
}

int main(){
	int n, i, A, B, C, k;
	FILE* in=fopen("kth.in","r");
	FILE* out=fopen("kth.out","w");
	fscanf(in, "%d %d %d %d %d", &n, &k, &A, &B, &C);
	int U[n];
	fscanf(in, "%d %d", &U[1], &U[2]);
	for(i=3;i<=n;++i){
		U[i]=A*U[i-2]+B*U[i-1]+C;
	}
	sort(U, 1, n);
	fprintf(out, "%d", U[k]);
	fclose(in);
	fclose(out);
	return 0;
}




















