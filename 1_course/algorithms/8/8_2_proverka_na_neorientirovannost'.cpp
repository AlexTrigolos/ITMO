#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n, m;
	fin >> n;
	int Arr[n][n];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			fin >> Arr[i][j];
		}
	}
	int flag = 1;
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			if(i == j && Arr[i][j] == 1){
				flag = 0;
				break;
			}else if(Arr[i][j] != Arr[j][i]){
				flag = 0;
			}
		}
		if(flag == 0){
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