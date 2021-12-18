#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

struct Edge{
	int u, v;
	long long int w;
};

int main(){
	std::ifstream fin("path.in");
	std::ofstream fout("path.out");
	int i, j, k, n, m, s, a, b, c;
	std::vector<int> error;
	bool flag;
	fin >> n >> m >> s;
	Edge edge[m];
	long long int d[n];
	int p[n];
	for(i = 0; i < m; i++){
		fin >> a >> b >> c;
		d[i] = std::numeric_limits<long long int>::max() - 10;
		edge[i].u = a - 1;
		p[i] = -1;
		edge[i].v = b - 1;
		edge[i].w = c;
	}
	d[s - 1] = 0;
	for(i = 0; i < n; i++){
		flag = false;
		for(j = 0; j < m; j++){
			int now = d[edge[j].v];
			if(d[edge[j].v] > d[edge[j].u] + edge[j].w){
				d[edge[j].v] = std::max(std::numeric_limits<long long int>::min(), d[edge[j].u] + edge[j].w);
				p[edge[j].v] = edge[j].u;
				flag = true;
				if(now != std::numeric_limits<long long int>::max() - 10)
				error.push_back(edge[j].v);
			}
		}
		if(flag == false){
			break;
		}
	}
	if(flag != false){
		std::vector<int> vec;
		int used[n] = {false};
		for(i = 0; i < error.size(); i++){
		std::cout << error[i] + 1 << " ";
			if(used[error[i]] == false){
				int now = error[i];
				for(j = 0; j < n; j++){
					now = p[now];
					used[now] = true;
				}
				vec.push_back(now);
			}
		}
		for(i = 0; i < vec.size(); i++){
			std::cout << vec[i] << " ";
		}
		for(i = 0; i < vec.size(); i++){
			flag = false;
			for(j = vec[i]; j != vec[i] || flag != true; j = p[j]){
				std::cout << j << " " << vec[i] << " ";
				d[j] = std::numeric_limits<long long int>::min() + 10;
				flag = true;
			}
			std::cout << "\n\n\n\n\n";
		}
	}
	for(i = 0; i < n; i++){
		if(d[i] == std::numeric_limits<long long int>::max()){
			fout << "*\n";
		}else if(d[i] != std::numeric_limits<long long int>::min() + 10){
			fout << d[i] << "\n";
		}else{
			fout << "-\n";
		}
	}
	return 0;
}