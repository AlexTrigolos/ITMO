#include <stdio.h>

int partition(int* U, int p, int r){
	int pivot=U[(r+p)/2], o;
	int i=p;
	int j=r;
	while(p<=r){
		while(U[i] < pivot)
			i++;
		while(U[j] > pivot)
			j--;
		if(i>=j){
			break;
		}
		o=U[i];
		U[i]=U[j];
		U[j]=o;
		if(U[i]==U[j]){
			i++;
			j--;
		}
	}
	return j;
}

void sort(int* U, int p, int r, int k){
	if(p<r){
		int q=partition(U, p, r);
		if (k<q){
			sort(U, p, q, k);
		} else if (k>q){
			sort(U, q+1, r, k);
		} else {
			sort(U, q, q, k);
		}
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
	sort(U, 1, n, k);
	fprintf(out, "%d", U[k]);
	fclose(in);
	fclose(out);
	return 0;
}