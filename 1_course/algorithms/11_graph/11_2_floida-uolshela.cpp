#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

int main(){
	ifstream fin("pathsg.in");
	ofstream fout("pathsg.out");
	int n, m, i, j, a, b, c;
	fin >> n >> m;
	int mas[n][n];
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(i == j){
				mas[i][j] = 0;
			}else{
				mas[i][j] = numeric_limits<int>::max() / 2;
			}
		}
	}
	for(i = 0; i < m; i++){
		fin >> a >> b >> c;
		mas[a - 1][b - 1] = c;
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				mas[j][k] = min(mas[j][k], mas[j][i] + mas[i][k]);
			}
		}
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			fout << mas[i][j] << " ";
		}
		fout << "\n";
	}
	
	return 0;
}