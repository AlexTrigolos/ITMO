#include <stdio.h>

int check(double h2, double* a, double left, double right, int n){
	int rus = 0;
	a[1] = h2;
	for(int i = 2; i < n; ++i){
		a[i] = 2* a[i - 1] + 2 - a[i - 2];
		if(a[i] <= 0.0001 && a[i]>= -0.0001){
			rus++;
		} else if(a[i] < -0.0001){
			return -1;
		}
	}
	if(rus > 1){
		return -1;
	} else if(rus == 0){
		return 0;
	} else if(rus == 1){
		return 1;
	}
}

void find(double* a, int n, double left, double right){
	double mid = (right + left) / 2;
	int rus = check(mid, a, left, right, n);
	if(rus == -1){
		find(a, n, mid, right);
	} else if(rus == 0){
		find(a, n, left, mid);
	}
}

int main(){
	int n;
	double A;
	double h2;
	double hn = 0;
	int i;
	int j = 0;
	int k = 0;
	FILE* in = fopen("garland.in","r");
	FILE* out = fopen("garland.out","w");
	fscanf(in, "%d%lf", &n, &A);
	double a[n];
	a[0] = A;
	find(a, n, 0, A);
	// 3 || + 2; 4 || + 4; 5 || + 6; 6 || + 8
	for(i = 3; i <= n; i++){
		j += 2;
		k += j;
	}
	hn = (n-1)*a[1] -(n-2)*A + k;
	fprintf(out, "%.2lf", hn);
	fclose(in);
	fclose(out);
	return 0;
}