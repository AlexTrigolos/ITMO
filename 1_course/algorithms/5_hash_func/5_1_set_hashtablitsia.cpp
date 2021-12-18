#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

struct List{
	int value;
	List* next;
	List* prev;
};

void insert(List** place, int x){
	List* first = place[0];
	List* pred = place[1];
	List* now = new List();
	now->value = x;
	now->next = NULL;
	if(first == NULL){
		now->prev = NULL;
		place[1] = now;
		place[0] = now;
	}else{
		while(first->next != NULL && first->value != x){
			first = first->next;
		}
		if(first->value != x){
			now->prev = pred;
			pred->next = now;
			place[1] = now;
		}
	}
}

void deletenum(List** place, int x){
	List* first = place[0];
	if(first != NULL){
		while(first->next != NULL && first->value != x){
			first = first->next;
		}
		if(first->value == x && first->next == NULL && first->prev == NULL){
			place[0] = NULL;
			place[1] = NULL;
		}else if(first->value == x && first->next != NULL && first->prev != NULL){
			List* w = first->prev;
			List* q = first->next;
			q->prev = first->prev;
			w->next = first->next;
		}else if(first->value == x && first->next == NULL && first->prev != NULL){
			List* w = first->prev;
			w->next = NULL;
			place[1] = w;
		}else if(first->value == x && first->next != NULL && first->prev == NULL){
			List* q = first->next;
			q->prev = NULL;
			place[0] = q;
		}
	}
}

int exists(List** place, int x){
	List* first = place[0];
	if(first == NULL){
		return 0;
	}
	while(first->next != NULL && first->value != x){
		first = first->next;
	}
	if(first->value != x){
		return 0;
	}else{
		return 1;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ifstream fin("set.in");
	ofstream fout("set.out");
	string str;
	int x;
	int del = 6210863;
	List* Arr[6210863][2] = {{NULL, NULL}};//{first, pred}
	while(fin >> str){
		fin >> x;
		if(str == "insert"){
			insert(&Arr[abs(x % del)][2], x);
		}else if(str == "delete"){
			deletenum(&Arr[abs(x % del)][2], x);
		}else if(str == "exists"){
			if(exists(&Arr[abs(x % del)][2], x) == 0){
				fout << "false" << endl;
			}else{
				fout << "true" << endl;
			}
		}
	}
	return 0;
}