#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct List{
	string value;
	string key;
	List* next;
	List* prev;
};

int hashing(string key){
	int sum = 0;
	for(int i = 0; i < key.size(); i++){
		sum = (sum * 97 + key[i]) % 200003;
	}
	return sum;
}

void put(List** place, string key, string value){
	if(place[0] == NULL){
		List* now = new List();
		now->next = NULL;
		now->prev = NULL;
		now->key = key;
		now->value = value;
		place[0] = now;
		place[1] = now;
	}else{
		List* first = place[0];
		while(first->next != NULL && first->key != key){
			first = first->next;
		}
		if(first->key == key){
			first->value = value;
		}else{
			List* now = new List();
			place[1]->next = now;
			now->next = NULL;
			now->prev = place[1];
			now->value = value;
			now->key = key;
			place[1] = now;
		}
	}
}

void deletehash(List** place, string key){
	if(place[0] != NULL){
		List* first = place[0];
		while(first->next != NULL && first->key != key){
			first = first->next;
		}
		if(first->next != NULL && first->prev != NULL && first->key == key){
			/*List* q = first->next;
			List* w = first->prev;
			q->prev = first->prev;
			w->next = first->next;*/
			first->next->prev = first->prev;
			first->prev->next = first->next;
		}else if(first->next == NULL && first->prev != NULL && first->key == key){
			first->prev->next = NULL;
			place[1] = first->prev;
		}else if(first->next != NULL && first->prev == NULL && first->key == key){
			first->next->prev = NULL;
			place[0] = first->next;
		}else if(first->next == NULL && first->prev == NULL && first->key == key){
			place[0] = NULL;
			place[1] = NULL;
		}
	}	
}

void get(List** place, string key, ofstream& fout){
	if(place[0] != NULL){
		List* first = place[0];
		while(first->next != NULL && first->key != key){
			first = first->next;
		}
		if(first->key == key){
			fout << first->value << endl;
		}else{
			fout << "none" << endl;
		}
	}else{
		fout << "none" << endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ifstream fin("map.in");
	ofstream fout("map.out");
	string str, key, value;
	List* Arr[200003][2] = {{NULL, NULL}};
	while(fin >> str){
		fin >> key;
		int hash = hashing(key);
		if(str == "put"){
			fin >> value;
			put(&Arr[hash][2], key, value);
		}else if(str == "get"){
			get(&Arr[hash][2], key, fout);
		}else if(str == "delete"){
			deletehash(&Arr[hash][2], key);
		}
	}
	return 0;
}

