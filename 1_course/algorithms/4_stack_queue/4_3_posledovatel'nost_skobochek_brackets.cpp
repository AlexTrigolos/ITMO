#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct List{
	char data;
	List* next;
};

void push(List** top, char p){
	List* q = new List();
	q->data = p;
	q->next = *top;
	*top = q;
}

void pop(List** top, char p, int *order){
	List* q = *top;
	if(q->data == '(' && p == ')'|| q->data == '[' && p == ']'){
		*top = q->next;
	} else {
		*order =+ 1;
	}
}

int main(){
	ifstream fin("brackets.in");
	ofstream fout("brackets.out");
	string str = {};
	fin >> str;
	while(str[0] == '(' || str[0] == ')' || str[0] == '[' || str[0] == ']'){
		int i = 0;
		int order = 0;
		int pushin = 0;
		int popout = 0;
		List* top = NULL;
		while(str[i] != '\0'){
			if(str[i] == '(' || str[i] == '['){
				push(&top, str[i]);
				pushin++;
			} else if (pushin == popout){
				order++;
				break;
			} else {
				pop(&top, str[i], &order);
				popout++;
				if(order != 0){
					break;
				}
			}
			++i;
		}
		if(order == 0 && popout == pushin){
			fout << "YES" << "\n";
		} else {
			fout << "NO" << "\n";
		}
		str = {};
		fin >> str;
	}
	return 0;
}