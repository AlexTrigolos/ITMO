#include <iostream>
#include <fstream>

using namespace std;

struct Dot{
	int k;
	int l;
	int r;
	int h;
	int rar;
};

void count(Dot* tree, int n){
	for(int i = n - 1; i >=0; i--){
		if(tree[i].r == -1 && tree[i].l == -1){
			tree[i].h = 1;
			tree[i].rar = 0;
		}else if(tree[i].r == -1){
			tree[i].h = tree[tree[i].l].h +1;
			tree[i].rar = -tree[tree[i].l].h;
		}else if(tree[i].l == -1){
			tree[i].h = tree[tree[i].r].h + 1;
			tree[i].rar = tree[tree[i].r].h;
		}else{
			tree[i].h = max(tree[tree[i].r].h, tree[tree[i].l].h) + 1;
			tree[i].rar = tree[tree[i].r].h - tree[tree[i].l].h;
		}
	}
}

int main(){
	ifstream fin("balance.in");
	ofstream fout("balance.out");
	int i, n;
	fin >> n;
	Dot tree[n];
	for(i = 0; i < n; i++){
		fin >> tree[i].k >> tree[i].l >> tree[i].r;
		tree[i].r--;
		tree[i].l--;
	}
	count((Dot*)&tree, n);
	for(int i = 0; i < n; i++){
		fout << tree[i].rar << "\n";
	}
	return 0;
}