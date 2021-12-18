#include <iostream>
#include <fstream>

using namespace std;

struct dot{
	int k;
	int l;
	int r;
};

int find(dot* tree, int osn){
	if(osn == -1){
		return 0;
	}else{
        return max(find(tree, tree[osn].l), find(tree, tree[osn].r)) + 1;
	}
}

int main(){
	ifstream fin("height.in");
	ofstream fout("height.out");
	int i, n;
	fin >> n;
	dot tree[n];
	for(i = 0; i < n; i++){
		fin >> tree[i].k >> tree[i].l >> tree[i].r;
		tree[i].r--;
		tree[i].l--;
	}
	if(n == 0){
		fout << 0;
	}else{
		fout << find(tree, 0);
	}
	return 0;
}