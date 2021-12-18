#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Set{
public:
	struct Node{
		string value;
		Node* next = nullptr;
		Node* prev = nullptr;
		Node* sled = nullptr;
	};
	Node* head = new Node;
	void put(string value, int* count, Node** last){
		if(head->next == nullptr){
			Node* now = new Node;
			now->value = value;
			if(*last != nullptr){
				(*last)->sled = now;
			}
			head->next = now;
			now->prev = *last;
			*last = now;
			(*count)++;
		}else{
			Node* first = head->next;
			while(first->next != nullptr && first->value != value){
				first = first->next;
			}
			if(first->value != value){
				Node* now = new Node;
				now->value = value;
				first->next = now;
				now->prev = *last;
				(*last)->sled = now;
				(*count)++;
				*last = now;
			}
		}
	}
	void del(string value, int* count, Node** last){
		if(head->next != nullptr){
			Node* first = head->next;
			Node* pred = head;
			while(first->next != nullptr && first->value != value){
				pred = first;
				first = first->next;
			}
			if(first->value == value){
				pred->next = first->next;
				if(first->prev){
					first->prev->sled = first->sled;
				}
				if(first->sled){
					first->sled->prev = first->prev;
				}
				if(first == *last){
					*last = (*last)->prev;
				}
				(*count)--;
			}
		}
	}
};

class Hashtabl{
private:
	int size = 103;
	int count = 0;
	Set::Node* last = nullptr;
public:
	int hash_func(string str){
		long long p_pow = 1;
		const int p = 53;
		int hash = 0;
		for(int i = 0; i < str.length(); i++){
			hash += (str[i] - 'A' + 1) * p_pow;
			p_pow *= p;
		}
		return abs(hash) % size;
	}
	Set* way = new Set[size];
	void put(string value){
		int hash = hash_func(value);
		way[hash].put(value, &count, &last);
	}
	void del(string value){
		int hash = hash_func(value);
		way[hash].del(value, &count, &last);
	}
	void get(ofstream& fout){
		fout << count;
		Set::Node* time = last;
		while(time != nullptr){
			fout << ' ' << time->value;
			time = time->prev;
		}
	}
};

class List{
public:
	struct Node{
		string key;
		Node* next = nullptr;
		Hashtabl link;
	};
	Node *head = new Node;
	void put(string key, string value){
		if(head->next == nullptr){
			Node* now = new Node;
			now->key = key;
			now->link.put(value);
			head->next = now;
		}else{
			Node* first = head->next;
			while(first->next != nullptr && first->key != key){
				first = first->next;
			}
			if(first->key == key){
				first->link.put(value);
			}else{
				Node* now = new Node;
				now->key = key;
				now->link.put(value);
				first->next = now;
			}
		}
	}
	void del(string key, string value){
		if(head->next != nullptr){
			Node* first = head->next;
			while(first->next != nullptr && first->key != key){
				first = first->next;
			}
			if(first->key == key){
				first->link.del(value);
			}
		}
	}
	void delall(string key){
		if(head->next != nullptr){
			Node* first = head->next;
			Node* prev = head;
			while(first->next != nullptr && first->key != key){
				prev = first;
				first = first->next;
			}
			if(first->key == key){
				prev->next = first->next;
			}
		}
	}
	void get(string key, ofstream& fout){
		if(head->next != nullptr){
			Node* first = head->next;
			while(first->next != nullptr && first->key != key){
				first = first->next;
			}
			if(first->key == key){
				first->link.get(fout);
				fout << "\n";
			}else{
				fout << '0' << "\n";
			}
		}else{
			fout << '0' << "\n";
		}
	}
};

class Mult{
private:
	int size = 103;
public:
	List* talb = new List[size];
	int hash_func(string str){
		long long p_pow = 1;
		const int p = 53;
		int hash = 0;
		for(int i = 0; i < str.length(); i++){
			hash += (str[i] - 'A' + 1) * p_pow;
			p_pow *= p;
		}
		return abs(hash) % size;
	}
	void put(string key, string value){
		int hash = hash_func(key);
		talb[hash].put(key, value);
	}
	void del(string key, string value){
		int hash = hash_func(key);
		talb[hash].del(key, value);
	}
	void delall(string key){
		int hash = hash_func(key);
		talb[hash].delall(key);
	}
	void get(string key, ofstream& fout){
		int hash = hash_func(key);
		talb[hash].get(key, fout);
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ifstream fin("multimap.in");
	ofstream fout("multimap.out");
	Mult tabl;
	string str, key, value;
	while(fin >> str >> key){
		if(str == "put"){
			fin >> value;
			tabl.put(key, value);
		}else if(str == "delete"){
			fin >> value;
			tabl.del(key, value);
		}else if(str == "deleteall"){
			tabl.delall(key);
		}else{
			tabl.get(key, fout);
		}
	}
	return 0;
}



