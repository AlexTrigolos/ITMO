#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

bool bfs(int point, const vector<vector<pair<int, int>>>& vec){
	unordered_set<int> used;
	queue <int> queue;
	used.insert(point);
	queue.push(point);
	while(!queue.empty()){
		int q = queue.front();
		queue.pop();
		for(auto i : vec[q]){
			int to = i.first;
			if(used.find(to) == used.end()){
				used.insert(to);
				queue.push(to);
			}
		}
	}
	return used.size() == vec.size();
}

void dfssort(int point, vector<vector<pair<int, int>>>& vec, vector<int>& color, vector<int>& order){
	color[point] = 1;
	for(auto edge : vec[point]){
		int to = edge.first;
		if(color[to] == 0){
			dfssort(to, vec, color, order);
		}
	}
	order.push_back(point);
}

void dfstransposed(int point, int component, vector<vector<pair<int, int>>>& vec, vector<int>& color, vector<int>& components){
    color[point] = 1;
    components[point] = component;
    for (auto edge : vec[point]){
        int to = edge.first;
        if (color[to] == 0){
            dfstransposed(to, component, vec, color, components);
        }
    }
}


int condensation(vector<vector<pair<int, int>>>& vec, vector<int>& components){
	int n = vec.size();
	vector<vector<pair<int, int>>> transposed(n);
	for(int from = 0; from < n; from++){
		for(int edge = 0; edge < vec[from].size(); edge++){
			int to = vec[from][edge].first;
			int weight = vec[from][edge].second;
			transposed[to].push_back({from, weight});
		}
	}
	vector<int> color(n, 0);
	vector<int> order;
	for(int i = 0; i < n; i++){
		if(color[i] == 0){
			dfssort(i, vec, color, order);
		}
	}
	reverse(order.begin(), order.end());
	color.assign(n, 0);
	int component = 0;
	for(int i : order){
		if(color[i] == 0){
            dfstransposed(i, component++, transposed, color, components);
		}
	}
	return component;
}

int findmst(vector<vector<pair<int, int>>>& vec, int n, int root){
	int res = 0;
	int minedge[n];
	for(int i = 0; i < n; i++){
		minedge[i] = numeric_limits<int>::max();
	}
	for(auto q : vec){
		for(auto w : q){
			int to = w.first;
			int weight = w.second;
			minedge[to] = min(weight, minedge[to]);
		}
	}
	for(int i = 0; i < vec.size(); i++){
		if(i != root){
			res += minedge[i];
		}
	}
	vector<vector<pair<int, int>>> zero;
	for(int from = 0; from < vec.size(); from++){
		for(int edge = 0; edge < vec[from].size(); edge++){
			int to = vec[from][edge].first;
			int weight = vec[from][edge].second;
			if(weight == minedge[to]){
			zero[from].push_back({to, weight - minedge[to]});
			}
		}
	}
	if(bfs(root, zero)){
		return res;
	}
	vector<int> newcomponents(n);
	int comp = condensation(zero, newcomponents);
	vector<vector<pair<int, int>>> newedge(comp);
	for(int from = 0; from < vec.size(); from++){
		for(auto edge : vec[from]){
			int to = edge.first;
			int weight = edge.second;
			if(newcomponents[from] != newcomponents[to]){
				newedge[newcomponents[from]].push_back({newcomponents[to], weight - minedge[to]});
			}
		}
	}
	res += findmst(newedge, comp, newcomponents[root]);
	
	return res;
}

int main(){
	ifstream fin("chinese.in");
	ofstream fout("chinese.out");
	int n, m, i, j, a, b, c;
	vector <vector <pair<int, int>>> vec(n);
	for(i = 0; i < m; i++){
		fin >> a >> b >> c;
		vec[a - 1].push_back({b - 1, c});
	}
	cout << "!";
	if(bfs(0, vec) == true){
		fout << "YES\n" << findmst(vec, n, 0);
	}else{
		fout << "NO";
	}
	return 0;
}