#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <cmath>

using namespace std;

bool bfs(int** flows, int** mas, int n){
	int d[n];
	for(int i = 0; i < n; i++){
		d[i] = numeric_limits<int>::max();
	}
	d[0] = 0;
	queue<int> q;
	q.push(0);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int v = 0; v < n; v++){
			if(d[v] == numeric_limits<int>::max() && mas[u][v] - flows[u][v] > 0){
				d[v] = u;
				if(v == n - 1){
					int w = v;
					int flow = numeric_limits<int>::max();
					for(u = d[w]; v != 0; v = u, u = d[u]){
						flow = min(flow, mas[u][v] - flows[u][v]);
					}
					for(u = d[w], v = w; v != 0; v = u, u = d[u]){
						flows[u][v] += flow;
						flows[v][u] -= flow;
					}
					return true;
				}
				q.push(v);
			}
		}
	}
	return false;
}

int main(){
	int i, j, n, m, u, v, c, l, r;
	ifstream fin("circulation.in");
	ofstream fout("circulation.out");
	fin >> n >> m;
	n += 2;
	int** mincap = new int* [n];
	int** mas = new int* [n];
	int** flows = new int* [n];
	for(i = 0; i < n; i++){
		flows[i] = new int [n];
		mincap[i] = new int [n];
		mas[i] = new int [n];
		for(j = 0; j < n; j++){
			flows[i][j] = 0;
			mas[i][j] = 0;
		}
	}
	int edge[m][2];
	for(i = 0; i < m; i++){
		fin >> u >> v >> l >> r;
		edge[i][0] = u;
		edge[i][1] = v;
		mincap[u][v] = l;
		mas[0][v] += l;
		mas[u][n - 1] += l;
		mas[u][v] = r - l;
	}
	while(bfs(flows, mas, n));
	for(i = 0; i < n; i++){
		if(flows[0][i] < mas[0][i]){
			fout << "NO";
			return 0;
		}
	}
	fout << "YES\n";
	for(i = 0; i < m; i++){
		u = edge[i][0];
		v = edge[i][1];
		fout << flows[u][v] + mincap[u][v] << "\n";
	}
	return 0;
}