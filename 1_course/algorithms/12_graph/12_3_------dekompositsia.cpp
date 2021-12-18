#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

int dfs(int** mas, bool* visited, int point, int t, int max, vector<pair<int, int>>* vec, vector<int>& res, int& lvl){
	if(point == t){
		return max;
	}
	visited[point] = true;
	for(int i = 0; i <= t; i++){
		if(!visited[i] && mas[point][i] > 0){
			int delta = dfs(mas, visited, i, t, min(max, mas[point][i]), vec, res, lvl);
			if(delta > 0){
				lvl++;
				for(int j = 0; j < vec[point].size(); j++){
					if(vec[point][j].first == i){
						res.push_back(vec[point][j].second);
					}
				}
				mas[point][i] -= delta;
				mas[i][point] += delta;
				return delta;
			}
		}
	}
	return 0;
}

int maxflow(int** mas, bool* visited, int s, int t, vector<pair<int, int>>* vec, vector<int>& res, vector<int>& start){
	int flow = 0;
	int now;
	int lvl;
	for(;;){
		lvl = 0;
		now = dfs(mas, visited, s, t, numeric_limits<int>::max(), vec, res, lvl);
		if(now == 0){
			return flow;
		}
		start.push_back(now);
		start.push_back(lvl);
		flow += now;
		for(int i = 0; i <= t; i++){
			visited[i] = false;
		}
	}
}

int main(){
	int i, j, n, m, u, v, c;
	ifstream fin("decomposition.in");
	ofstream fout("decomposition.out");
	fin >> n >> m;
	int** mas = new int* [n];
	for(i = 0; i < n; i++){
		mas[i] = new int [n];
		for(j = 0; j < n; j++){
			mas[i][j] = 0;
		}
	}
	vector<int> start;
	vector<int> res;
	vector<pair<int, int>> vec[m];
	for(i = 0; i < m; i++){
		fin >> u >> v >> c;
		vec[u - 1].push_back({v - 1, i + 1});
		mas[u - 1][v - 1] = c;
	}
	bool visited[n] = {false};
	int size;
	int e = 0;
	fout << maxflow(mas, visited, 0, n - 1, vec, res, start) << "\n";
	for(i = 0; i < start.size(); i += 2){
		size = start[i + 1];
		fout << start[i] << " " << size;
		e = e + size;
		for(j = 0; j < size; j++){
			fout << " " << res[e - j - 1];
		}
		fout << "\n";
	}
	return 0;
}