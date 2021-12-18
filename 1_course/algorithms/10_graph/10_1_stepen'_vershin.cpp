#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n, m, i, a, b;
	fin >> n >> m;
	int Arr[n] = {0};
	for(i = 0; i < m; ++i){
		fin >> a >> b;
		Arr[a - 1]++;
		Arr[b - 1]++;
	}
	for(i = 0; i < n; i++){
		fout << Arr[i] << " ";
	}
	return 0;
}