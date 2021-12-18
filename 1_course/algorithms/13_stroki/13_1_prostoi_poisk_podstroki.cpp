#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	ifstream fin("search1.in");
	ofstream fout("search1.out");
	string str;
	int i, b = 0, j = 0;
	getline(fin, str);
	vector<char> p;
	for(i = 0; i < str.size(); i++){
		p.push_back(str[i]);
	}
	getline(fin, str);
	vector<char> t;
	for(i = 0; i < str.size(); i++){
		t.push_back(str[i]);
	}
	vector<int> ex;
	for(i = 0; i < t.size(); i++){
		if(p[j] == t[i]){
			b++;
			j++;
		}else{
			if(b == p.size()){
				ex.push_back(i - p.size() + 1);
			}
			i -= b;
			b = 0;
			j = 0;
		}
	}
	if(b == p.size()){
		ex.push_back(i - p.size() + 1);
	}
	fout << ex.size() << "\n";
	for(i = 0; i < ex.size(); i++){
		fout << ex[i] << " ";
	}
	return 0;
}