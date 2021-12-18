#pragma once
#include <iostream>
#include "3.h"

using namespace std;

class Menu{
	private:
	int var;
	double a, b, c, d;
	void print_menu(){
		system("cls");
		cout << "What do you want to do?" << endl;
		cout << "1. Multiplication a complex number by a real number." << endl;
		cout << "2. The addition of two complex numbers." << endl;
		cout << "3. Multiplication of two complex numbers." << endl;
		cout << "4. Length of a complex number." << endl;
		cout << "5. Add to stack." << endl;
		cout << "6. Remove from stack." << endl;
		cout << "7. Display a stack." << endl;
		cout << "8. Exit." << endl;
	}
	int take_variant(){
		int s;
		cin >> s;
		return s;
	}
	
	public:
	int start(){
		Stack vec;
		int size = 0;
		int num;
		do{
			print_menu();
			var = take_variant();
			if(var == 1){
				cout << "Enter a, b and c, where z = a + b * i, c is real number." << endl;
				cin >> a >> b >> c;
				Point q(a, b);
				Point w;
				w = q * c;
				cout << "z = " << w.x << " + " << w.y << " * i\n";
				w = q.operator*(c);
				cout << "z = " << w.x << " + " << w.y << " * i\n";
			}else if(var == 2){
				cout << "Enter a, b, c and d, where z1 = a + b * i, z2 = c + d * i.\n";
				cin >> a >> b >> c >> d;
				Point e(a, b);
				Point r(c, d);
				Point t;
				t = e + r;
				cout << "z = " << t.x << " + " << t.y << " * i\n";
				t = e.operator+(r);
				cout << "z = " << t.x << " + " << t.y << " * i\n";
			}else if(var == 3){
				cout << "Enter a, b, c and d, where z1 = a + b * i, z2 = c + d * i. Multiplication of two complex numbers.\n";
				cin >> a >> b >> c >> d;
				Point y(a, b);
				Point u(c, d);
				Point i;
				i = y * u;
				cout << "z = " << i.x << " + " << i.y << " * i\n";
				i = y.operator*(u);
				cout << "z = " << i.x << " + " << i.y << " * i\n";
			}else if(var == 4){
				cout << "Enter a and b, where z = a + b * i. Length of a complex number.\n";
				cin >> a >> b;
				Point o(a, b);
				cout << (double) o << "\n";
				cout << o.operator double() << "\n";
			}else if(var == 5){
				if(size < 100){
					cout << "Enter 1 number.\n";
					cin >> num;
					vec = vec << num;
					size++;
				}else{
					cout << "Stack is full\n" << endl;
				}
			}else if(var == 6){
				if(size >= 1){
					vec = vec >> 5;
					size--;
				}else{
					cout << "Stack is empty" << endl;
				}
			}else if(var == 7){
				if(size == 0){
					cout << "Stack is empty" << endl;
				}else{
					vec.display();
				}
			}
			if(var != 8){
				system("pause");
			}
		}while(var != 8);
		return 0;
	}
	
	
};