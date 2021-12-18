#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	int Arr[n][n] = {};
	int a, b;
	for(int i = 0; i < m; i++){
		fin >> a >> b;
		Arr[a - 1][b - 1] = 1;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			fout << Arr[i][j] << " ";
		}
		fout << endl;
	}
	return 0;
}