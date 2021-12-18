#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

bool kuhn(const int v, vector<int>* edge, vector<bool>& fst, vector<int>& sec){
	if(fst[v]){
		return false;
	}
	fst[v] = true;
	for(int i = 0; i < edge[v].size(); i++){
		int to = edge[v][i];
		if(sec[to] == -1 || kuhn(sec[to], edge, fst, sec)){
			sec[to] = v;
			return true;
		}
	}
	return false;
}

int main(){
	int i, j, n, m, u, v, k;
	ifstream fin("matching.in");
	ofstream fout("matching.out");
	fin >> n >> m >> k;
	vector<int> sec;
	vector<int> edge[n];
	vector<bool> fst;
	for(i = 0; i < k; i++){
		fin >> u >> v;
		edge[u - 1].push_back(v - 1);
	}
	sec.assign(m, -1);
	int max = 0;
	for(i = 0; i < n; i++){
		fst.assign(n, false);
		if(kuhn(i, edge, fst, sec)){
			max++;
		}
	}
	fout << max;
	return 0;
}