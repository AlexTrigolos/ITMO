#include <iostream>
#include <vector>

using namespace std;

int main(){
	string str;
	int i, j, size;
	cin >> size;
	cin >> str;
	vector<unsigned char> s;
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
	vector<vector<int>> b(n + 1, vector<int>(size));
	for(i = 0; i < n + 1; i++){
		for(j = 0; j < size; j++){
			b[i][j] = 0;
			if(i > 0 && j != (int)s[i] - 97){
				b[i][j] = b[z[i]][j];
			}else if(j == (int)s[i] - 97){
				b[i][j] = i + 1;
			}else{
				b[i][j] = i;
			}
		}
	}
	for(i = 0; i < n + 1; i++){
		for(j = 0; j < size; j++){
			cout << b[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}