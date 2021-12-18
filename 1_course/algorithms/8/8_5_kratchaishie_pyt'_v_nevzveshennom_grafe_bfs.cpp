#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

queue <int> bfs(int x, queue <int> z, vector <int>* list, bool* used, int* way, int l){
	for(int i = 0; i < list[x].size(); i++){
		if(used[list[x][i]] == false){
			used[list[x][i]] = true;
			z.push(list[x][i]);
		}
	}
	way[x] = l;
	return z;
}

int main(){
	ifstream fin("pathbge1.in");
	ofstream fout("pathbge1.out");
	int n, m, a, b, i, count = 0, j = 1;
	fin >> n >> m;
	bool used[n];
	int way[n] = {0};
	vector <int> list[n];
	for(int i = 0; i < m; ++i){
		fin >> a >> b;
		list[a - 1].push_back(b - 1);
		list[b - 1].push_back(a - 1);
	}
	for(int i = 1; i < n; ++i){
		used[i] = false;
	}
	used[0] = true;
	queue <int> q;
	queue <int> w;
	q = bfs(0, q, list, used, way, 0);
	i = 1;
	while(i < n){
		while(q.empty() == false){
			int y = q.front();
			q.pop();
			i++;
			w = bfs(y, w, list, used, way, j);
		}
		j++;
		while(w.empty() == false){
			int y = w.front();
			w.pop();
			i++;
			q = bfs(y, q, list, used, way, j);
		}
		j++;
	}
	for(int i = 0; i < n; i++){
		fout << way[i] << " ";
	}
	return 0;
}