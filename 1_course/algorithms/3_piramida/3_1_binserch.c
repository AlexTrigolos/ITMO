#include <stdio.h>

int binSearchL(int *Arr, int k, int l, int r){
	int m;
	while(l < r - 1){
		m = (r + l) / 2;
		if(Arr[m] < k){
			l = m;
		} else{
			r = m;
		}
	}
	if(Arr[1] == k){
		r = 1;
	}
	if(Arr[r] != k){
		r = -1;
	}
	return r;
}

int binSearchR(int *Arr, int k, int l, int r, int n){
	int m;
	while(l < r - 1){
		m = (r + l) / 2;
		if(Arr[m] <= k){
			l = m;
		} else{
			r = m;
		}
	}
	if(Arr[n] == k){
		l = n;
	}
	if(Arr[l] != k){
		l = -1;
	}
	return l;
}

int main(){
	int k;
	int i;
	int n;
	int m;
	FILE* in = fopen("binsearch.in","r");
	FILE* out = fopen("binsearch.out","w");
	fscanf(in, "%d", &n);
	int Arr[n];
	int l = 1;
	int r = n;
	for(i = 1; i <= n; ++i){
		fscanf(in, "%d", &Arr[i]);
	}
	fscanf(in, "%d", &m);
	for(i = 1; i <= m; ++i){
		fscanf(in, "%d", &k);
		fprintf(out, "%d %d\n", binSearchL(Arr, k, l, r), binSearchR(Arr, k, l, r, n));
	}
	fclose(in);
	fclose(out);
	return 0;
}