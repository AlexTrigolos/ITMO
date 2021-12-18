#include <fstream>
#include <iostream>

using namespace std;

struct List{
	int data;
	List* next;
};

void push(List** first, int p, List** prev){
	List* q = new List();
	q->data = p;
	if(*prev != NULL){
		List* w = *prev;
		w->next = q;
	} else {
		*first = q;
	}
	q->next = NULL;
	*prev = q;
}

int pop(List** first, List** prev){
	List* q = *first;
	int r = q->data;
	if(q->next != NULL){
		*first = q->next;
	} else {
		*prev = NULL;
	}
	return r;
}

int main(){
	List* prev = NULL;
	List* first = NULL;
	int M, i;
	ifstream fin("queue.in");
	ofstream fout("queue.out");
	fin >> M;
	char s;
	for(i = 0; i < M; ++i){
		fin >> s;
		if(s == '+'){
			int o;
			fin >> o;
			push(&first, o, &prev);
		} else {
			fout << pop(&first, &prev) << '\n';
		}
	}
	return 0;
}