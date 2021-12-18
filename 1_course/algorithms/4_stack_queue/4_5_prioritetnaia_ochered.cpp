#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

struct List{
	int value;
	int	num;
	List* next;
	List* prev;
};

void push(int value, int num, List** pred, List** first){
	List* q = new List();
	q->value = value;
	q->num = num;
	q->next = NULL;
	if(*first == NULL){
		q->prev = NULL;
		*first = q;
	}else{
		List* a = *pred;
		a->next = q;
		q->prev = *pred;
	}
	*pred = q;
}

int extractmin(List** first, List** pred){
	int min = 2147483647;
	List* q = *first;
	List* extmin = *first;
	while(q != NULL){
		if(q->value < min){
			extmin = q;
			extmin->next = q->next;
			extmin->prev = q->prev;
			min = q->value;
		}
		q = q->next;
	}
	if(extmin->next == NULL && extmin->prev == NULL){
		*first = NULL;
		*pred = NULL;
	}else if(extmin->next == NULL){
		List* e = extmin->prev;
		e->next = NULL;
		*pred = e;
	}else if(extmin->prev == NULL){
		List* e = extmin->next;
		e->prev = NULL;
		*first = e;
	}else{
		List* e = extmin->next;
		List* w = extmin->prev;
		e->prev = extmin->prev;
		w->next = extmin->next;
	}
	return min;
}

void decreasekey(int line, int newvalue, List** first, List** pred){
	List* q = *first;
	List* f = *pred;
	while(q->num != line){
		q = q->next;
	}
	q->value = newvalue;
}

int main(){
	List* first = NULL;
	List* pred = NULL;
	ifstream fin("priorityqueue.in");
	ofstream fout("priorityqueue.out");
	string str;
	int i = 1, a, b;
	while(fin >> str){
		if(str == "push"){
			fin >> a;
			push(a, i, &pred, &first);
		}else if(str == "extract-min"){
			if(first == NULL){
				cout << "*" << endl;
			}else{
				a = extractmin(&first, &pred);
				cout << a << endl;
			}
		}else if(str == "decrease-key"){
			fin >> a >> b;
			decreasekey(a, b, &first, &pred);
		}
		
		i++;
	}
	return 0;
}