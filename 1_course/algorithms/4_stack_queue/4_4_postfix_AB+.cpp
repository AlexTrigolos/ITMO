#include <fstream>
#include <iostream>
#include <string>

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

void popadd(List** top){
	List* q = *top;
	List* w = q->next;
	w->data += q->data;
	*top = w;
}

void popmult(List** top){
	List* q = *top;
	List* w = q->next;
	w->data *= q->data;
	*top = w;
}

void popsub(List** top){
	List* q = *top;
	List* w = q->next;
	w->data = w->data - q->data;
	*top = w;
}

int main(){
	List* top = NULL;
	int num = 0;
	int opr = 0;
	ifstream fin("postfix.in");
	ofstream fout("postfix.out");
	char str;
	fin >> str;
	while(num - opr > 1 || (int)str > 47){
		if((int)str > 47 && (int)str < 58){
			push(&top, (int)str - 48);
			num++;
		} else {
			if((int)str == 42){
				popmult(&top);
			} else if ((int)str == 43){
				popadd(&top);
			} else {
				popsub(&top);
			}
			opr++;
		}
		fin >> str;
	}
	fout << top->data;
	return 0;
}