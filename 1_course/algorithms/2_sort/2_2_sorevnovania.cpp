#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>

using namespace std;

struct inf{
	string country;
	string man;
};

void merge(inf* A, int p, int q, int r){
	int i, j;
	int n1 = q - p + 1;
	int n2 = r - q;
	inf L[n1];
	inf R[n2];
	for(i = 0; i < n1; i++){
		L[i].country = A[p + i].country;
		L[i].man = A[p + i].man;
	}
	for(j = 0; j < n2; j++){
		R[j].country = A[q + j + 1].country;
		R[j].man = A[q + j + 1].man;
	}
	j = 0;
	i = 0;
	int k = p;
	while(i < n1 && j < n2){
		if(L[i].country <= R[j].country){
			A[k] = L[i];
			i++;
		} else {
			A[k] = R[j];
			j++;
		}
		k++;
	}
	while(i < n1){
		A[k] = L[i];
		i++;
		k++;
	}
	while(j < n2){
		A[k] = R[j];
		j++;
		k++;
	}
}

void sort(inf* A, int p, int r){
	if(p < r){
		int q = (r + p) / 2;
		sort(A, p, q);
		sort(A, q + 1, r);
		merge(A, p, q, r);		
	}
}


int main(){
	int n, m, i, k;
	ifstream fin("race.in");
	ofstream fout("race.out");
	fin >> n;
	inf race[n];
	for(i = 0; i < n; i++){
		fin >> race[i].country >> race[i].man;
	}
	sort(race, 0, n-1);
	for(i = 0; i < n; i++){
		if(i == 0 || race[i].country != race[i - 1].country){
			fout << "=== " << race[i].country << " ===\n";
		}
		fout << race[i].man << "\n";
	}
	return 0;
}