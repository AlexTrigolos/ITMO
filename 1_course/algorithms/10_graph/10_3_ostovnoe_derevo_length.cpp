#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct edge{
	int x, y, w;
	edge(){}
	edge(int x, int y, int w)
	:x(x), y(y), w(w)
	{}
};

void make_set(int v, int* parent, int* rank){
	parent[v] = v;
	rank[v] = 0;
}

int find_set(int v, int* parent){
	if(v == parent[v]){
		return v;
	}
	return parent[v] = find_set(parent[v], parent);
}

bool union_sets(int a, int b, int* parent, int* rank){
	a = find_set(a, parent);
	b = find_set(b, parent);
	if(a != b){
		parent[b] = a;
		if(rank[a] < rank[b]){
			swap(a, b);
		}
		parent[b] = a;
		if(rank[a] == rank[b]){
			rank++;
		}
		return true;
	}
	return false;
}


void merge(edge* A, int p, int q, int r){
	int i, j;
	int n1 = q - p + 1;
	int n2 = r - q;
	edge L[n1];
	edge R[n2];
	for(i = 0; i < n1; i++)
		L[i]=A[p + i];
	for(j = 0; j < n2; j++)
		R[j] = A[q + j + 1];
	j = 0;
	i = 0;
	int k = p;
	while(i < n1 && j < n2){
		if(L[i].w <= R[j].w){
			A[k] = L[i];
			i++;
		} else {
			A[k] = R[j];
			j++;
		}
		k++;
	}
	while(i < n1){
		A[k] = L[i];
		i++;
		k++;
	}
	while(j < n2){
		A[k] = R[j];
		j++;
		k++;
	}
}

void sort(edge* A, int p, int r){
	//p левая граница, r правая граница
	if(p<r){
		int q = (r + p) / 2;
		sort(A, p, q);
		sort(A, q + 1, r);
		merge(A, p, q, r);		
	}
}

int main(){
	ifstream fin("spantree3.in");
	ofstream fout("spantree3.out");
	int i, n, m;
	long long sum = 0;
	fin >> n >> m;
	edge Arr[m];
	for(i = 0; i < m; i++){
		fin >> Arr[i].x >> Arr[i].y >> Arr[i].w;
		Arr[i].x--;
		Arr[i].y--;
	}
	sort(Arr, 0, m - 1);
	int parent[n], rank[n];
	for(i = 0; i < n; i++)
		make_set(i, parent, rank);
	vector <edge> ans;
	for(i = 0; i < m; i++){
		int a = Arr[i].x, b = Arr[i].y;
		if(union_sets(parent[a], parent[b], parent, rank) == true){
			ans.push_back(Arr[i]);
		}
	}
	for(i = 0; i < ans.size(); i++){
		sum += ans[i].w;
	}
	fout << sum << endl;
	return 0;
}