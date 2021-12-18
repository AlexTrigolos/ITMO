#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int main(){
    int i, j, n;
    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");
    fin >> n;
    vector<pair<int, int>> edge[n];
    int d[n] = {0}, p[n], a;
    for(i = 0; i < n; i++){
        p[i] = -1;
        for(j = 0; j < n; j++){
            fin >> a;
            if(a != 1000000000){
                edge[i].push_back({j, a});
            }
        }
    }
    int flag;
    for(int k = 0; k < n; k++){
        flag = -1;
        for(i = 0; i < n; i++){
            for(j = 0; j < edge[i].size(); j++){
                if(d[edge[i][j].first] > d[i] + edge[i][j].second){
                    d[edge[i][j].first] = max(numeric_limits<int>::min(), d[i] + edge[i][j].second);
                    p[edge[i][j].first] = i;
                    flag = edge[i][j].first;
                }
            }
        }
        if(flag == -1){
            break;
        }
    }
    if(flag != -1){
        vector<int> mas;
        int time = flag;
        for(j = 0; j < n; j++){
            time = p[time];
        }
        for(j = time; ; j = p[j]){
            mas.push_back(j);
            if(j == time && mas.size() > 1){
                break;
            }
        }
        reverse(mas.begin(), mas.end());
        fout << "YES\n" << mas.size() << "\n";
        for(i = 0; i < mas.size(); i++){
            fout << mas[i] + 1 << " ";
        }
    }else{
        fout << "NO";
    }
    return 0;
}