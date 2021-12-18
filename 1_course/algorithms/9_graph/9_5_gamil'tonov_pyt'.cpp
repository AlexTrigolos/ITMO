#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int q, vector <int>* list, char* used, stack <int>& steck){
	used[q] = 'b';
	for(int i = 0; i < list[q].size(); ++i){
		int time = list[q][i];
		if(used[time] == 'w'){
			dfs(time, list, used, steck);
		}
	}
	steck.push(q);
}

int main(){
	ifstream fin("hamiltonian.in");
	ofstream fout("hamiltonian.out");
	int n, m, a, b, i, flag;
	fin >> n >> m;
	char used[n];
	stack <int> steck;
	vector <int> list[n];
	for(int i = 0; i < m; ++i){
		fin >> a >> b;
		list[a - 1].push_back(b - 1);
	}
	for(int i = 0; i < n; ++i){
		used[i] = 'w';
	}
	int e;
	for(int i = 0; i < n; i++){
		if(used[i] == 'w'){
			dfs(i, list, used, steck);
		}
	}
	while(steck.size() > 1){
		a = steck.top();
		steck.pop();
		b = steck.top();
		flag = 0;
		for(i = 0; i < list[a].size(); i++){
			if(list[a][i] == b)
				flag = 1;
		}
		if(flag == 0)
			break;
	}
	if(flag == 0)
		fout << "NO";
	else fout << "YES";
	
	
	return 0;
}