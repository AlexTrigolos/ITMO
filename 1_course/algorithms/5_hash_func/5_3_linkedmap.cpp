#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

struct List{
	string value;
	string key;
	List* next;
	List* qnext;
	List* qprev;
};

int hash_func(string key) {
    long long p_pow = 1;
    const int p = 53;
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash += (key[i] - 'A' + 1) * p_pow;
        p_pow *= p;
    }
    return abs(hash) % 250007;
}

void put(List** place, string key, string value, List** conect){
	if(*place == NULL){
		List* now = new List();
		now->key = key;
		now->value = value;
		if(*conect != NULL){
			(*conect)->qnext = now;
			now->qprev = *conect;
		}
		*conect = now;
		*place = now;
	}else{
		List* first = *place;
		while(first->next != NULL && first->key != key){
			first = first->next;
		}
		if(first->key == key){
			first->value = value;
		}else{
			List* now = new List();
			first->next = now;
			now->value = value;
			now->key = key;
			(*conect)->qnext = now;
			now->qprev = *conect;
			*conect = now;
		}
	}
}

void deletehash(List** place, string key, List** conect){
	if(*place != NULL){
		List* first = *place;
		List* prev = NULL;
		while(first->next != NULL && first->key != key){
			prev = first;
			first = first->next;
		}
		if(first->key == key && first->next != NULL){
			prev->next == first->next;
			if(first->qprev != NULL){
				first->qprev->qnext = first->qnext;
			}
			if(first->qnext != NULL){
				first->qnext->qprev = first->qprev;
			}
			if(first == *conect){
				*conect = (*conect)->qprev;
				(*conect)->qnext == NULL;
			}
		}else if(first->key == key){
			*place = NULL;
			if(first->qprev != NULL){
				first->qprev->qnext = first->qnext;
			}
			if(first->qnext != NULL){
				first->qnext->qprev = first->qprev;
			}
			if(first == *conect){
				*conect = (*conect)->qprev;
				(*conect)->qnext == NULL;
			}
		}
	}
}

void get(List** place, string key, ofstream& fout){
	if(*place != NULL){
		List* first = *place;
		while(first->key != key && first->next != NULL){
			first = first->next;
		}
		if(first->key == key){
			fout << first->value << "\n";
		}else{
			fout << "none" << "\n";
		}
	}else{
		fout << "none" << "\n";
	}
}

void prev(List** place, string key, ofstream& fout){
	if(*place != NULL){
		List* first = *place;
		while(first->key != key && first->next != NULL){
			first = first->next;
		}
		if(first->key == key && first->qprev != NULL){
			fout << first->qprev->value << "\n";
		}else{
			fout << "none" << "\n";
		}
	}else{
		fout << "none" << "\n";
	}
}

void next(List** place, string key, ofstream& fout){
	if(*place != NULL){
		List* first = *place;
		while(first->key != key && first->next != NULL){
			first = first->next;
		}
		if(first->key == key && first->qnext != NULL){
			fout << first->qnext->value << "\n";
		}else{
			fout << "none" << "\n";
		}
	}else{
		fout << "none" << "\n";
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ifstream fin("linkedmap.in");
	ofstream fout("linkedmap.out");
	string str, key, value;
	List* Arr[250007] = {NULL};
	List* conect = NULL;
	while(fin >> str){
		fin >> key;
		int hash = hash_func(key);
		if(str == "put"){
			fin >> value;
			put(&Arr[hash], key, value, &conect);
		}else if(str == "get"){
			get(&Arr[hash], key, fout);
		}else if(str == "delete"){
			deletehash(&Arr[hash], key, &conect);
		}else if(str == "prev"){
			prev(&Arr[hash], key, fout);
		}else if(str == "next"){
			next(&Arr[hash], key, fout);
		}
	}
	return 0;
}