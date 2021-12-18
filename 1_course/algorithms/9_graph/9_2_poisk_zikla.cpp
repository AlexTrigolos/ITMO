#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

int dfs(int q, vector <int>* list, char* used, stack <int>& steck){
	used[q] = 'g';
	for(int i = 0; i < list[q].size(); ++i){
		int time = list[q][i];
		if(used[time] == 'w'){
			int e = dfs(time, list, used, steck);
			if(e >= 0){
				steck.push(q);
				if(q != e){
					return e;
				}else{
					return -1;
				}
			}else if(e == -1){
				return -1;
			}
		}else if(used[time] == 'g'){
			steck.push(q);
			return time;
		}
	}
	used[q] = 'b';
	return -2;
}

int main(){
	ifstream fin("cycle.in");
	ofstream fout("cycle.out");
	int n, m, a, b, i;
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
			e = dfs(i, list, used, steck);
			if(e == -1){
				break;
			}
		}
	}
	if(e == -2){
		fout << "NO";
	}else if(e == -1){
		fout << "YES\n";
		while(steck.empty() == false){
			fout << steck.top() + 1 << " ";
			steck.pop();
		}
	}
	return 0;
}