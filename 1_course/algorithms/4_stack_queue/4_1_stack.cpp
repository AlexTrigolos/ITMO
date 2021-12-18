#include <fstream>
#include <iostream>

using namespace std;

struct List{
	int data;
	List* next;
};

void push(List** top, int p){
	List* q = new List();
	q->data = p;
	q->next = *top;
	*top = q;
}

int pop(List** top){
	List* q = *top;
	int r = q->data;
	*top = q->next;
	return r;
}

int main(){
	List* top = NULL;
	int M, i;
	ifstream fin("stack.in");
	ofstream fout("stack.out");
	fin >> M;
	char s;
	for(i = 0; i < M; ++i){
		fin >> s;
		if(s == '+'){
			int o;
			fin >> o;
			push(&top, o);
		} else {
			fout << pop(&top) << '\n';
		}
	}
	return 0;
}