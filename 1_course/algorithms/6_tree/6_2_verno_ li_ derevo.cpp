#include <iostream>
#include <fstream>

using namespace std;

struct dot{
	int k;
	int l;
	int r;
};

void put(dot* tree, int* Arr, int osn, int* i){
	if(osn != -1){
		put(tree, Arr, tree[osn].l, i);
		Arr[*i] = tree[osn].k;
		(*i)++;
		put(tree, Arr, tree[osn].r, i);
	}
}

bool check(dot* tree){
	int Arr[200000], i = 0;
	put(tree, Arr, 0, &i);
	for(int k = 0; k < i - 1; k++){
		if(Arr[k] >= Arr[k + 1]){
			return false;
		}
	}
	return true;
}

int main(){
	ifstream fin("check.in");
	ofstream fout("check.out");
	int i, n;
	fin >> n;
	dot tree[n];
	for(i = 0; i < n; i++){
		fin >> tree[i].k >> tree[i].l >> tree[i].r;
		tree[i].r--;
		tree[i].l--;
	}
	if(n == 0 || check(tree)){
		fout << "YES";
	}else{
		fout << "NO";
	}
	return 0;
}