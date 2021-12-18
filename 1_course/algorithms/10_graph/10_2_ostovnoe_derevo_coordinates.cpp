#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
	ifstream fin("spantree.in");
	ofstream fout("spantree.out");
	int i, m, n, a, b, c;
	fin >> n;
	int Arr[n][2];
	for(i = 0; i < n; i++){
		fin >> Arr[i][0] >> Arr[i][1];
	}
	bool used[n] = {0};
	double Len[n];
	Len[0] = 0;
	used[0] = true;
	for(i = 1; i < n; i++){
		Len[i] = sqrt(pow(Arr[0][0] - Arr[i][0],2) + pow(Arr[0][1] - Arr[i][1],2));
	}
	int w = 1, now;
	double sum = 0, min, buf;
	while(w < n){
		min = 1000000000;
		for(i = 1; i < n; i++){
			if(Len[i] < min && used[i] == false){
				now = i;
				min = Len[i];
			}
		}
		used[now] = true;
		sum += min;
		w++;
		for(i = 0; i < n; i++){
			if(used[i] == false){
				buf = sqrt(pow(Arr[now][0] - Arr[i][0],2) + pow(Arr[now][1] - Arr[i][1],2));
				if(buf < Len[i]){
					Len[i] = buf;
				}
			}
		}
	}
	fout << fixed << setprecision(3) << sum;
	return 0;
}