#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>

using namespace std;

void radixSort(string* A, int n, int m, int k){
	int i, j;
	string B[n] = {};
	m--;
	for(i = 1; i <= k; ++i){
		int C[26] = {};
		for(j = 0; j < n; j++){
		C[static_cast<int>(A[j][m]) - 96]++;
		}
		for(j = 2; j < 26; j++){
			C[j] = C[j] + C[j-1];
		}
		for(j = 0; j < n; j++){
			B[C[static_cast<int>(A[j][m]) - 97]++] = A[j];
		}
		for(j = 0; j < n; j++){
			A[j] = B[j];
		}
		m--;
	}
	/*
	int i, j, y;
	string l;
	for(i = 1; i <= k; i++){
		for(y = 1; y < n; y++){
		l = A[y].lol;
		j = y - 1;
			while(l[m - i] < A[j].lol[m - i] && j >= 0){
				A[j + 1].lol = A[j].lol;
				j--;
			}
		A[j + 1].lol = l;
		}
	}*/
}

int main(){
	int n, m, i, k;
	ifstream fin("radixsort.in");
	ofstream fout("radixsort.out");
	fin >> n >> m >> k;
	string str[n];
	for(i=0;i<n;i++){
		fin >> str[i];
	}
	radixSort(str, n, m, k);
	for(i=0;i<n;i++){
		fout << str[i] << "\n";
	}
	return 0;
}














