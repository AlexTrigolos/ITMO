#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	ifstream fin("prefix.in");
	ofstream fout("prefix.out");
	string str;
	int i, j = 0;
	getline(fin, str);
	vector<char> s;
	for(i = 0; i < str.size(); i++){
		s.push_back(str[i]);
	}
	int n = s.size();
	vector<int> z(n + 1, 0);
	i = 1;
	j = 0;
	while(i < n){
		if(s[i] == s[j]){
			z[i + 1] = j + 1;
			i++;
			j++;
		}else{
			if(j > 0){
				j = z[j];
			}else{
				z[i + 1] = 0;
				i++;
			}
		}
	}
	for(i = 1; i <= n; i++){
		fout << z[i] << " ";
	}
	return 0;
}