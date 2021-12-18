#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	ifstream fin("search2.in");
	ofstream fout("search2.out");
	string str;
	int i, j = 0;
	getline(fin, str);
	vector<char> s;
	for(i = 0; i < str.size(); i++){
		s.push_back(str[i]);
	}
	int m = s.size();
	s.push_back('#');
	getline(fin, str);
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
	int sum = 0;
	for(int i = 0; i <= n; i++){
		if(z[i] == m){
			sum++;
		}
	}
	fout << sum << "\n";
	for(i = 0; i <= n; i++){
		if(z[i] == m){
			fout << i - 2 * m << " ";
			if(!--sum){
				break;
			}
		}
	}
	return 0;
}