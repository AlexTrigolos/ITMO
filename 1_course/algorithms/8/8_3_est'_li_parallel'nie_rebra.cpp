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
		Arr[a - 1][b - 1] += 1;
	}
	int flag = 0;
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(Arr[i][j] == Arr[j][i] && Arr[i][j] >= 1 || Arr[i][j] >= 2 || Arr[j][i] >= 2){
				flag = 1;
				break;
			}
		}
		if(flag == 1){
			break;
		}
	}
	if(flag == 1){
		fout << "YES"; 
	}else{
		fout << "NO";
	}
	return 0;
}