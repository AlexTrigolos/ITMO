#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

int dfs(int** mas, bool* visited, int point, int t, int max){
	if(point == t){
		return max;
	}
	visited[point] = true;
	for(int i = 0; i <= t; i++){
		if(!visited[i] && mas[point][i] > 0){
			int delta = dfs(mas, visited, i, t, min(max, mas[point][i]));
			if(delta > 0){
				mas[point][i] -= delta;
				mas[i][point] += delta;
				return delta;
			}
		}
	}
	return 0;
}

int maxflow(int** mas, bool* visited, int s, int t){
	int flow = 0;
	int now;
	for(;;){
		now = dfs(mas, visited, s, t, numeric_limits<int>::max());
		if(now == 0){
			return flow;
		}
		flow += now;
		for(int i = 0; i <= t; i++){
			visited[i] = false;
		}
	}
}

int main(){
	int i, j, n, m, u, v, c;
	ifstream fin("maxflow.in");
	ofstream fout("maxflow.out");
	fin >> n >> m;
	int** mas = new int* [n];
	for(i = 0; i < n; i++){
		mas[i] = new int [n];
		for(j = 0; j < n; j++){
			mas[i][j] = 0;
		}
	}
	for(i = 0; i < m; i++){
		fin >> u >> v >> c;
		mas[u - 1][v - 1] = c;
	}
	bool visited[n] = {false};
	fout << maxflow(mas, visited, 0, n - 1);
	return 0;
}