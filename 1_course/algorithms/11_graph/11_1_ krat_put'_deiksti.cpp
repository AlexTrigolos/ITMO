#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int main(){
	ifstream fin("pathmgep.in");
	ofstream fout("pathmgep.out");
	int n, s, i, j, f;
	fin >> n >> s >> f;
	int mas[n][n];
	long long int way[n];
	bool used[n] = {false};
	for(i = 0; i < n; i++){
		way[i] = -100;
		for(j = 0; j < n; j++){
			fin >> mas[i][j];
		}
	}
	way[s - 1] = 0;
	for(i = 0; i < n; i++){
		int v = -1;
		for(int j = 0; j < n; j++){
			if(used[j] == false && (v == -1 || (way[v] == -100 && way[j] != -100) || (way[v] > way[j] && way[j] != -100))){
				v = j;
			}
		}
		if(way[v] == -100){
			break;
		}
		used[v] = true;
		for(int e = 0; e < n; e++){
			if(mas[v][e] >= 0){
				if(way[e] > way[v] + mas[v][e] || way[e] == -100){
					way[e] = way[v] + mas[v][e];
				}
			}
		}
	}
	if(way[f - 1] != -100){
		fout << way[f - 1];
	}else{
		fout << "-1";
	}
	return 0;
}