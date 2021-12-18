#include <iostream>
#include <string.h>
#include <fstream>
#include <locale.h>
using namespace std;
//списсок всех словоформ
struct List{
	string val;
	List* next;
};
//список всех иникальных словоформ
struct Node{
	string val;
	Node* next;
};
//список слов из словаря с их частотой(слов)
struct Slovar{
	string val;
	int num;
	Slovar* next;
};
//список возможных ошибок
struct Miss{
	string val;
	Miss* next;
};
//список слов для замены, возможные для них замены, их редакторское расстояние и частота(из словаря)
struct Spsk{
	string text;
	string slov;
	int raz;
	int num;
	Spsk* next;
};
//добавление уникального слова из начального текста
void sec(Node** perv, string val){
	if(*perv == NULL){
		Node* now = new Node();
		now->val = val;
		*perv = now;
	}else{
		Node* v = *perv;
		while(v->next != NULL){
			v = v->next;
		}
		Node* now = new Node();
		now->val = val;
		v->next = now;
	}
}
//добавление нового слова из начального текста
void add(List** first, string val, Node** perv){
	int count = 0;
	if(*first == NULL){
		List* now = new List();
		now->val = val;
		*first = now;
	}else{
		List* v = *first;
		while(v->next != NULL){
			if(v->val == val){
				count++;
			}
			v = v->next;
		}
		List* now = new List();
		now->val = val;
		v->next = now;
	}
	if(count == 0){
		sec(perv, val);
	}
}
//добавление слов из словаря
void slovarik(Slovar** one, string val, int num){
	if(*one == NULL){
		Slovar* now = new Slovar();
		now->val = val;
		now->num = num;
		*one = now;
	}else{
		Slovar* v = *one;
		while(v->next != NULL){
			v = v->next;
		}
		Slovar* now = new Slovar();
		now->val = val;
		now->num = num;
		v->next = now;
	}
}
//добавление слов в которых возможна ошибка
void mbmiss(Miss** tre, string val){
	if(*tre == NULL){
		Miss* now = new Miss();
		now->val = val;
		*tre = now;
	}else{
		Miss* v = *tre;
		while(v->next != NULL){
			v = v->next;
		}
		Miss* now = new Miss();
		now->val = val;
		v->next = now;
	}
}
//добавление в список какие слова на кикие слова возможна замена их редакторское расстояние и частота из словаря
void spisok(string text, string slov, int raz, int num, Spsk** jkl){
	if(*jkl == NULL){
		Spsk* now = new Spsk();
		now->text = text;
		now->slov = slov;
		now->raz = raz;
		now->num = num;
		*jkl = now;
	}else{
		Spsk* v = *jkl;
		while(v->next != NULL){
			v = v->next;
		}
		Spsk* now = new Spsk();
		now->text = text;
		now->slov = slov;
		now->raz = raz;
		now->num = num;
		v->next = now;
	}
}
//главная функция
int main(){
	setlocale(LC_ALL, "Russian");
	ifstream fin("brain092.txt");
	ofstream fout("lollik.txt");
	string str, zxc;
	List* first = NULL;
	Node* perv = NULL;
	Slovar* one = NULL;
	Miss* tre = NULL;
	Spsk* jkl = NULL;
	Spsk* rand = NULL;
	int i, j, size, count = 0, k = 0, num, schet = 0, buff, sizer, sizee, lol;
	//считываение файла
	while(fin >> str){
		i = 0;
		size = str.size();
		//удаление символов
		while(i < size){
			if(str[i] == ',' || str[i] == '(' || str[i] == ')' || str[i] == '.' || str[i] == '!' || str[i] == '?' || str[i] == ';' || str[i] == ':' || str[i] == '»' || str[i] == '«'){
				for(j = i; j < size; j++){
					str[j] = str[j + 1];
				}
				str.erase(str.begin() + j-1 );
				size--;
				i--;
			}else{
				//приводим к строчным буквам
				str[i] = tolower(str[i]);
			}
			i++;
		}
		//добавление в список
		add(&first, str, &perv);
		k++;//считает кольчество словоформ
	}
	//записываем в список слова из словаря и их частоту
	ifstream finik("dict1.txt");
	while(finik >> str){
		finik >> num;
		slovarik(&one, str, num);
	}
	//считаем разные словоформы и разные словоформы из словаря; задание 2
	Node* w = perv;
	Slovar* e = one;
	while(w != NULL){
		e = one;
		buff = schet;
		while(e != NULL){
			if(w->val == e->val){
				schet++;
			}
			e = e->next;
		}
		if(buff == schet){
			mbmiss(&tre, w->val);
		}
		w = w->next;
		count++;
	}
	cout << k << endl;//словоформы
	cout << count << endl;//разные словоформы
	cout << schet << endl;//разных словоформ присутствует в словаре
	//
	int asdfg = count - schet;
	cout << asdfg << endl;//разных словоформ не присутствует в словаре(потенциальные ошибки)
	//200+ строк для нахождения возможных ошибочных слов и то на какие их можно поменять; задание 3
	Miss* r = tre;
	while(r != NULL){
		e = one;
		sizer = r->val.size();
		while(e != NULL){
			lol = 0;
			sizee = e->val.size();
			//для разницы больше 2
			if(sizer - sizee > 2){
				i = 0;
				while(i <= sizer - sizee){
					for(j = 0 + i; j < sizee + i; j++){
						if(r->val[j] != e->val[j]){
							lol++;
						}
					}
					//если начало совпадают
					if(lol < 2 && i == 0){
						string rty;
						for(j; j < sizer; j++){
							rty[j - sizee] = r->val[j];
						}
						Slovar* sqrt = one;
						int ark = lol;
						while(sqrt != NULL){
							for(k = 0; k < sizer - sizee; k++){
								if(rty[k] != sqrt->val[k]){
									ark++;
								}
							}
							sqrt = sqrt->next;
						}
						if(ark < 2){
							spisok(r->val, e->val, ark + 1, e->num, &jkl);//
						}
						//если совпадают концы
					}else if(lol < 2 && i == sizer - sizee){
						string rty;
						for(j = 0; j < sizee; j++){
							rty[j] = r->val[j];
						}
						Slovar* sqrt = one;
						int ark = lol;
						while(sqrt != NULL){
							for(k = 0; k < sizer - sizee; k++){
								if(rty[k] != sqrt->val[k]){
									ark++;
								}
							}
							sqrt = sqrt->next;
						}
						if(ark < 2){
							spisok(r->val, e->val, ark + 1, e->num, &jkl);//
						}
						//в остальных случаях когда не конец и не середина
					}else if(lol < 2){
						string rty, dfg;
						Slovar* sqrt = one;
						int h = j;
						for(j; j < sizer; j++){
							rty[j - h] = r->val[j];
						}
						for(j = 0; j < h - sizee; j++){
							dfg[j] = r->val[j];
						}
						int ark = lol;
						while(sqrt != NULL){
							for(k = 0; k < sizer - sizee; k++){
								if(rty[k] != sqrt->val[k]){
									ark++;
								}
							}
							sqrt = sqrt->next;
						}
						sqrt = one;
						while(sqrt != NULL){
							for(k = 0; k < sizer - sizee; k++){
								if(dfg[k] != sqrt->val[k]){
									ark++;
								}
							}
							sqrt = sqrt->next;
						}
						if(ark < 2){
							spisok(r->val, e->val, ark + 1, e->num, &jkl);//
						}
					}
					i++;
				}
				//когда длина слов равна
			}else if(sizer - sizee == 0){
				for(i = 0; i < sizee; i++){
					if(r->val[i] != e->val[i]){
						lol++;
					}
				}
				if(lol < 3){
					spisok(r->val, e->val, lol, e->num, &jkl);
				}
				//когда длина одного больше чем второга на 1
			}else if(abs(sizer - sizee) == 1){
				//длина ошибочного больше возможного исправления
				string time;
				if(sizer > sizee){
					for(i = 0; i < sizee; i++){
						time[i] = r->val[i];
					}
					for(i = 0; i < sizee; i++){
						if(time[i] != e->val[i]){
							lol++;
						}
					}
					if(lol < 2){
						spisok(r->val, e->val, lol + 1, e->num, &jkl);
					}else{
						lol = 0;
						for(i = 0; i < sizee; i++){
							time[i] = r->val[i + 1];
						}
						for(i = 0; i < sizee; i++){
							if(time[i] != e->val[i]){
								lol++;
							}
						}
						if(lol < 2){
							spisok(r->val, e->val, lol + 1, e->num, &jkl);
						}
					}
					//наоборот
				}else{
					for(i = 0; i < sizer; i++){
						time[i] = e->val[i];
					}
					for(i = 0; i < sizer; i++){
						if(time[i] != r->val[i]){
							lol++;
						}
					}
					if(lol < 2){
						spisok(r->val, e->val, lol + 1, e->num, &jkl);
					}else{
						lol = 0;
						for(i = 0; i < sizer; i++){
							time[i] = e->val[i + 1];
						}
						for(i = 0; i < sizer; i++){
							if(time[i] != r->val[i]){
								lol++;
							}
						}
						if(lol < 2){
							spisok(r->val, e->val, lol + 1, e->num, &jkl);
						}else{
							lol = 0;
							j = 0;
							for(i = 0; i < sizer; i++, j++){
								if(r->val[i] != e->val[j]){
									lol++;
									i--;
								}
							}
							if(lol < 3){
								spisok(r->val, e->val, lol, e->num, &jkl);
							}else{
								lol = 0;
								j = 0;
								for(i = 0; i < sizer; i++, j++){
									if(r->val[i] != e->val[j]){
										lol++;
										j++;
									}
								}
								if(lol < 2){
									spisok(r->val, e->val, lol + 1, e->num, &jkl);
								}
							}
						}
					}
				}
				//для разницы в 2 символа
			}else if(abs(sizer - sizee) == 2){
				string time;
				//когда длина ошибочного меньше исправления
				if(sizee > sizer){
					for(i = 0; i < sizer; i++){
						time[i] = e->val[i];
					}
					if(time == r->val){
						spisok(r->val, e->val, 2, e->num, &jkl);
						
					}else{
						for(i = 0; i < sizer; i++){
							time[i] = e->val[i + 1];
						}
						if(time == r->val){
							spisok(r->val, e->val, 2, e->num, &jkl);
							
						}else{
							for(i = 0; i < sizer; i++){
								time[i] = e->val[i + 2];
							}
							if(time == r->val){
								spisok(r->val, e->val, 2, e->num, &jkl);
							}
						}
					}
					//наоборот
				}else{
					for(i = 0; i < sizee; i++){
						time[i] = r->val[i];
					}
					if(time == e->val){
						spisok(r->val, e->val, 2, e->num, &jkl);
						
					}else{
						for(i = 0; i < sizee; i++){
							time[i] = r->val[i + 1];
						}
						if(time == e->val){
							spisok(r->val, e->val, 2, e->num, &jkl);							
						}else{
							for(i = 0; i < sizee; i++){
								time[i] = r->val[i + 2];
							}
							if(time == e->val){
								spisok(r->val, e->val, 2, e->num, &jkl);
							}
						}
					}
				}
			}
			e = e->next;
		}
		r = r->next;
	}	
	Spsk* f;
	// поиск и замена словоформ которые возможные ошибки на максимально похожие исправления; завершение 3 задания
	List* q = first;
	r = tre;
	while(r != NULL){
		q = first;
		while(q != NULL){
			if(r->val == q->val){
				f = jkl;
				while(f != NULL){
					if(f->text == q->val){
						if(rand == NULL){
							rand = f;
						}else{
							if(rand->raz > f->raz){
								rand = f;
							}else if(rand->raz == f->raz && rand->num < f->num){
								rand = f;
							}
						}
					}
					f = f->next;
				}
				//замена уникальных и обычных словоформ
				w = perv;
				while(w->val != q->val){
					w = w->next;
				}
				w->val = rand->slov;
				q->val = rand->slov;
				rand = NULL;
			}
			q = q->next;
		}
		r = r->next;
	}
	//считаем 4 номер
	count = 0;
	schet = 0;
	k = 0;
	q = first;
	while(q != NULL){
		q = q->next;
		k++;
	}
	w = perv;
	e = one;
	while(w != NULL){
		e = one;
		buff = schet;
		while(e != NULL){
			if(w->val == e->val){
				schet++;
			}
			e = e->next;
		}
		if(buff == schet){
			mbmiss(&tre, w->val);
		}
		w = w->next;
		count++;
	}
	cout << k << endl;//словоформы
	cout << count << endl;//разные словоформы
	cout << schet << endl;//разных словоформ присутствует в словаре
	//замена словоформ ошибочных, то на какие заменили и разница между ними; 5 задание
	Spsk* c;
	f = jkl;
	int poriadok = 1;
	while(f != NULL){
		c = jkl;
		while(c != NULL){
			if(f->text == c->text){
				if(rand == NULL){
					rand = c;
				}else{
					if(rand->raz > c->raz){
						rand = c;
					}else if(rand->raz == c->raz && rand->num <= c->num){
						rand = c;
					}
				}
			}
			c = c->next;
		}
		cout << poriadok << ") " << rand->text << " - " << rand->slov << " - " << rand->raz << endl;
		while(f->next != NULL && f->text == f->next->text){
			f = f->next;
		}
			f = f->next;
		rand = NULL;
		poriadok++;
	}
	//вывод полученного текста
	q = first;
	while(q != NULL){
		fout << q->val << ' ';
		q = q->next;
	}
	return 0;
}