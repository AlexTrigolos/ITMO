#include <iostream>
#include <vector>
#include "4_1.h"

using namespace std;

void print_menu(){
	system("cls");
	cout << "What do you want to do?" << endl;
	cout << "1. Add figure." << endl;
	cout << "2. Show all figure." << endl;
	cout << "3. Sum of square of all figure." << endl;
	cout << "4. Sum of perimeter of all figure." << endl;
	cout << "5. Center of mass of the entire system.." << endl;
	cout << "6. Memory used by all instances of classes." << endl;
	cout << "7. Sort by weight." << endl;
	cout << "8. Exit." << endl;
}

int take_variant(){
	int s;
	cin >> s;
	return s;
}

int main(){
	int var, a, b;
	double S;
	vector <Triangle> tri;
	vector <Ellipse> ell;
	do{
		print_menu();
		var = take_variant();
		switch(var){
			case 1:
				cout << "1. Triangle\n2. Ellipse" << endl;
				cin >> a;
				if(a == 1){
					cout << "length = ";
					cin >> a;
					Triangle triangle(a);
					tri.push_back(triangle);
				}else{
					cout << "height = ";
					cin >> a;
					cout << "width = ";
					cin >> b;
					Ellipse ellipse(a, b);
					ell.push_back(ellipse);
				}
				break;
			case 2:
				if(tri.size() != 0)
					cout << "\ntriangle:\n";
				for(int i = 0; i < tri.size(); ++i){
					cout << "\t" << i + 1 << ". ";
					tri[i].draw();
				}
				if(ell.size() != 0)
					cout << "\nellipse:\n";
				for(int i = 0; i < ell.size(); ++i){
					cout << "\t" << i + 1 << ". ";
					ell[i].draw();
				}
				if(ell.size() == 0 && tri.size() == 0)
					cout << "empty\n";
				break;
			case 3:
				S = 0;
				for(int i = 0; i < ell.size(); ++i){
					S += ell[i].square();
				}
				for(int i = 0; i < tri.size(); ++i){
					S += tri[i].square();
				}
				cout << "Sum of square = " << S << ".\n";
				break;
			case 4:
				S = 0;
				for(int i = 0; i < ell.size(); ++i){
					S += ell[i].perimeter();
				}
				for(int i = 0; i < tri.size(); ++i){
					S += tri[i].perimeter();
				}
				cout << "Sum of perimeter = " << S << ".\n";
				break;
			case 5:
				
				break;
			case 6:
				a = 0;
				for(int i = 0; i < ell.size(); ++i){
					a += ell[i].size();
				}
				for(int i = 0; i < tri.size(); ++i){
					a += tri[i].size();
				}
				cout << "Memory used = " << a << ".\n";
				break;
			case 7:
				
				break;
		}
		if(var != 8){
			system("pause");
		}
	}while(var != 8);
	return 0;
}