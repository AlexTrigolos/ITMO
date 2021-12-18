#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

int bfs(queue <int>& z, int point, int lop, vector <int>* list, int* used){
	for(int i = 0; i < list[point].size(); i++){
		if(used[list[point][i]] == 0){
			used[list[point][i]] = lop;
			z.push(list[point][i]);
		}else if(used[point] == used[list[point][i]]){
			return 1;
		}
	}
	return 0;
}

int main(){
	ifstream fin("bipartite.in");
	ofstream fout("bipartite.out");
	int n, m, i, j, a, b;
	fin >> n >> m;
	vector <int> list[n];
	int used[n] = {0};
	for(int i = 0; i < m; ++i){
		fin >> a >> b;
		list[a - 1].push_back(b - 1);
		list[b - 1].push_back(a - 1);
	}
	queue <int> q;
	queue <int> w;
	for(a = 0; a < n; a++){
		if(used[a] == 0){
			used[a] = 2;
			j = bfs(q, a, 1, list, used);
			if(j == 1){
				break;
			}
			while(true){
				b = 0;
				while(q.empty() == false){
					int y = q.front();
					q.pop();
					b++;
					j = bfs(w, y, 2, list, used);
					if(j == 1){
						break;
					}
				}
				if(j == 1 || b == 0){
					break;
				}
				b = 0;
				while(w.empty() == false){
					int y = w.front();
					w.pop();
					b++;
					j = bfs(q, y, 1, list, used);
					if(j == 1){
						break;
					}
				}
				if(j == 1 || b == 0){
					break;
				}
			}
			if(j == 1){
				break;
			}
		}
	}
	if(j == 0)
		fout << "YES";
	else fout << "NO";
	return 0;
}