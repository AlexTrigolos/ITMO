#include <iostream>
#include <fstream>
#include <queue>
 
using namespace std;
 
void bfs(queue <int>* z, int point, int l, bool* Arr, int* used, int& k, int m){
    if(Arr[point + 1] == true && used[point + 1] == -1){
        used[point + 1] = l;
        z->push(point + 1);
        k++;
    }
    if(Arr[point - 1] == true && used[point - 1] == -1){
        used[point - 1] = l;
        z->push(point - 1);
        k++;
    }
    if(Arr[point + m + 2] == true && used[point + m + 2] == -1){
        used[point + m + 2] = l;
        z->push(point + m + 2);
        k++;
    }
    if(Arr[point - m - 2] == true && used[point - m - 2] == -1){
        used[point - m - 2] = l;
        z->push(point - m - 2);
        k++;
    }
}
 
int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m, start, finish, i, j, k = 1;
    char c;
    fin >> n >> m;
    bool Arr[(n + 2) * (m + 2)];
    string list[(n + 2) * (m + 2)];
    int way[(n + 2) * (m + 2)] = {0};
    for(i = 0; i < n + 2; ++i){
        if(i != 0 && i != n + 1){
            for(j = 0; j < m + 2; j++){
                if(j != 0 && j != m + 1){
                    fin >> c;
                    if(c == '.'){
                        Arr[i * (m + 2) + j] = true;
                    }else if(c == '#'){
                        Arr[i * (m + 2) + j] = false;
                    }else if(c == 'S'){
                        Arr[i * (m + 2) + j] = true;
                        start = i * (m + 2) + j;
                    }else{
                        Arr[i * (m + 2) + j] = true;
                        finish = i * (m + 2) + j;
                    }
                }else{
                    Arr[i * (m + 2) + j] = false;
                }
            }
        }else{
            for(j = 0; j < m + 2; j++){
                Arr[i * (m + 2) + j] = false;
            }
        }
    }
    queue <int> q;
    queue <int> w;
    int used[(n+2) * (m+2)], l = 1;
    for(i = 0; i < (n+2) * (m+2); i++){
        used[i] = -1;
    }
    used[start] = 0;
    q.push(start);
    while(used[finish] == -1 && k != 0){
        k = 0;
        while(q.empty() == false){
            int y = q.front();
            q.pop();
            bfs(&w, y, l, Arr, used, k, m);
            if(used[finish] != -1){
                break;
            }
        }
        if(k == 0 || used[finish] != -1){
            break;
        }
        l++;
        k = 0;
        while(w.empty() == false){
            int y = w.front();
            w.pop();
            bfs(&q, y, l, Arr, used, k, m);
            if(used[finish] != -1){
                break;
            }
        }
        l++;
    }
    if(used[finish] != -1){
        fout << used[finish] << "\n";
        string str;
        while(finish != start){
            if(used[finish] - 1 == used[finish - 1]){
                str = 'R' + str;
                finish -= 1;
            }else if(used[finish] - 1 == used[finish + 1]){
                str = 'L' + str;
                finish += 1;
            }else if(used[finish] - 1 == used[finish - m - 2]){
                str = 'D' + str;
                finish -= (2 + m);
            }else{
                str = 'U' + str;
                finish += (2 + m);
            }
        }
        fout << str;
    }else{
        fout << "-1";
    }
    return 0;
}