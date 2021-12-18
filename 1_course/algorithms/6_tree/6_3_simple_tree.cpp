#include <iostream>
#include <fstream>

using namespace std;

struct Dot{
	int value;
	Dot* left = nullptr;
	Dot* right = nullptr;
	Dot* par = nullptr;
};

Dot* next(Dot* head, int value){
	Dot* last = nullptr;
	while(head != nullptr){
		if(head->value > value){
			last = head;
			head = head->left;
		}else{
			head = head->right;
		}
	}
	return last;
}

Dot* prev(Dot* head, int value){
	Dot* last = nullptr;
	while(head != nullptr){
		if(head->value < value){
			last = head;
			head = head->right;
		}else{
			head = head->left;
		}
	}
	return last;
}

Dot* search(Dot* head, int value){
	if(head == nullptr || head->value == value){
		return head;
	}
	if(head->value < value){
		return search(head->right, value);
	}else{
		return search(head->left, value);
	}
}

void insert(Dot** head, int value){
	if(search((*head), value) == nullptr){
		Dot* time = (*head);
		Dot* now = new Dot;
		now->value = value;
		while(time != nullptr){
			now->par = time;
			if(value > time->value){
				time = time->right;
			}else{
				time = time->left;
			}
		}
		if(now->par != nullptr){
			if(now->value > now->par->value){
				now->par->right = now;
			}else{
				now->par->left = now;
			}
		}else{
			*head = now;
		}
	}
}

void del(Dot** head, int value){
	Dot* delel = search((*head), value);
	if(delel != nullptr){
		Dot* pred;
		Dot* child;
		if(delel->left == nullptr || delel->right == nullptr){
			pred = delel;
		}else{
			pred = next((*head), value);
		}
		if(pred->left != nullptr){
			child = pred->left;
		}else{
			child = pred->right;
		}
		if(child != nullptr){
			child->par = pred->par;
		}
		if(pred->par != nullptr){
			if(pred->par->left == pred){
				pred->par->left = child;
			}else{
				pred->par->right = child;
			}
		}else{
			(*head) = child;
		}
		if(pred != delel){
			delel->value = pred->value; 
		}
	}
}

bool exists(Dot* head, int value){
	if(search(head, value) != nullptr){
		return true;
	}else{
		return false;
	}
}

int main(){
	ifstream fin("bstsimple.in");
	ofstream fout("bstsimple.out");
	string str;
	int value;
	Dot* head = nullptr;
	while(fin >> str >> value){
		if(str == "insert"){
			insert(&head, value);
		}
		if(str == "delete"){
			del(&head, value);
		}
		if(str == "exists"){
			if(exists(head, value) == true){
				fout << "true\n";
			}else{
				fout << "false\n";
			}
		}
		if(str == "next"){
			Dot* nxt = next(head, value);
			if(nxt != nullptr){
				fout << nxt-> value << "\n";
			}else{
				fout << "none\n";
			}
		}
		if(str == "prev"){
			Dot* prv = prev(head, value);
			if(prv != nullptr){
				fout << prv->value << "\n";
			}else{
				fout << "none\n";
			}
		}
	}
	return 0;
}