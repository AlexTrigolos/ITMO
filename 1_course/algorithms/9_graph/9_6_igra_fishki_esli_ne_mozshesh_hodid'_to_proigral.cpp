#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

short dfs(int q, vector <int>* list, int* used, int way, short* win){
	used[q] = way;
	int j;
	for(int i = 0; i < list[q].size(); i++){
		int time = list[q][i];
		if(used[time] == 0){
			j = dfs(time, list, used, used[q] + 1, win);
			if(used[q] % 2 == 1 && win[q] != 1){
				win[q] = j;
			}else if(used[q] % 2 == 0 && win[q] != 2){
				win[q] = j;
			}
		}else{
			if(used[q] % 2 != used[time] % 2){
				if(used[q] % 2 == 0 && win[q] != 2){
					win[q] = win[time];
				}else if(used[q] % 2 == 1 && win[q] != 1){
					win[q] = win[time];
				}
			}else{
				if(used[q] % 2 == 0 && win[q] != 2){
					win[q] = (win[time] + 1) % 2;
				}else if(used[q] % 2 == 1 && win[q] != 1){
					win[q] = (win[time] + 1) % 2;
				}
			}
		}
	}
	if(win[q] == 0){
		if(used[q] % 2 == 0){
			win[q] = 1;
			return 1;
		}else{
			win[q] = 2;
			return 2;
		}
	}else{
		return win[q];
	}
}

int main(){
	ifstream fin("game.in");
	ofstream fout("game.out");
	int n, m, a, b, i, s, j;
	fin >> n >> m >> s;
	int used[n] = {0};
	short win[n] = {0};
	vector <int> list[n];
	for(i = 0; i < m; ++i){
		fin >> a >> b;
		list[a - 1].push_back(b - 1);
	}
	j = dfs(s - 1, list, used, 1, win);
	if(win[s - 1] == 2){
		fout << "Second player wins";
	}else{
		fout << "First player wins";
	}
	return 0;
}