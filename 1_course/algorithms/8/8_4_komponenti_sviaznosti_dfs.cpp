#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dfs(int q, vector <int>* list, bool* used, int count, vector <int>* comp){
	used[q] = true;
	comp[count].push_back(q);
	for(int i = 0; i < list[q].size(); ++i){
		int time = list[q][i];
		if(used[time] == false){
			dfs(time, list, used, count, comp);
		}
	}
}

int main(){
	ifstream fin("components.in");
	ofstream fout("components.out");
	int n, m, a, b, i, count = 0, j;
	fin >> n >> m;
	bool used[n];
	vector <int> list[n];
	vector <int> comp[n];
	for(int i = 0; i < m; ++i){
		fin >> a >> b;
		list[a - 1].push_back(b - 1);
		list[b - 1].push_back(a - 1);
	}
	for(int i = 0; i < n; ++i){
		used[i] = false;
	}
	for(int i = 0; i < n; i++){
		if(used[i] == false){
			dfs(i, list, used, count, comp);
			count++;
		}
	}
	int nom[n];
	for(int i = 0; i < count; i++){
		for(int j = 0; j < comp[i].size(); j++){
			nom[comp[i][j]] = i;
		}
	}
	fout << count << "\n";
	for(int i = 0; i < n; i++){
		fout << nom[i] + 1 << " ";
	}
	return 0;
}