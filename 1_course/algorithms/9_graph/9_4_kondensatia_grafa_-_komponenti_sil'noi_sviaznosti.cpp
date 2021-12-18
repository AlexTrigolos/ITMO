#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int point, vector <int>* list, bool* used, int* Arr, int& j){
	used[point] = true;
	for(int i = 0; i < list[point].size(); i++){
		if(used[list[point][i]] == false){
			dfs(list[point][i], list, used, Arr, j);
		}
	}
	Arr[j] = point;
	j++;
}

void dfs(bool* used, vector <int>* back, vector <int>* comp, int point, int count){
	used[point] = true;
	comp[count].push_back(point);
	for(int i = 0; i < back[point].size(); ++i){
		if(used[back[point][i]] == false){
			dfs(used, back, comp, back[point][i], count);
		}
	}
}

int main(){
	ifstream fin("cond.in");
	ofstream fout("cond.out");
	int n, m, i, count = 0, j, a, b;
	fin >> n >> m;
	vector <int> list[n];
	vector <int> back[n];
	vector <int> comp[n];
	int Arr[n];
	bool used[n] = {false};
	for(i = 0; i < m; ++i){
		fin >> a >> b;
		list[a - 1].push_back(b - 1);
		back[b - 1].push_back(a - 1);
	}
	j = 0;
	for(i = 0; i < n; i++){
		if(used[i] == false){
			dfs(i, list, used, Arr, j);
		}
	}
	for(i = 0; i < n; i++)
		used[i] = {false};
	for(i = n - 1; i >= 0; i--){
		if(used[Arr[i]] == false){
			dfs(used, back, comp, Arr[i], count);
			count++;
		}
	}
	int num[n];
	for(i = 0; i < count; i++){
		for(j = 0; j < comp[i].size(); j++){
			num[comp[i][j]] = i + 1;
		}
	}
	fout << count << "\n";
	for(i = 0; i < n; i++){
		fout << num[i] << " ";
	}
	return 0;
}