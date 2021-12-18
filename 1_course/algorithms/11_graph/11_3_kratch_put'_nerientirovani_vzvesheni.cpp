#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <set>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int i, j, n, m, a, b, c;
	ifstream fin("pathbgep.in");
	ofstream fout("pathbgep.out");
	fin >> n >> m;
	vector<pair<int, long long int>> vec[n];
	long long int way[n];
	for(i = 0; i < m; i++){
		fin >> a >> b >> c;
		vec[a - 1].push_back({b - 1, c});
		vec[b - 1].push_back({a - 1, c});
	}
	for(i = 0; i < n; i++){
		way[i] = numeric_limits<long long int>::max();
	}
	way[0] = 0;
	set<pair<int, int>> set;
	set.insert(make_pair(way[0], 0));
	while(set.empty() == false){
		int v = set.begin()->second;
		set.erase(set.begin());
		for(i = 0; i < vec[v].size(); i++){
			if(way[vec[v][i].first] > way[v] + vec[v][i].second){
				way[vec[v][i].first] = way[v] + vec[v][i].second;
				set.insert(make_pair(way[vec[v][i].first], vec[v][i].first));
			}
		}
	}
	for(i = 0; i < n; i++){
		fout << way[i] << " ";
	}
	return 0;
}