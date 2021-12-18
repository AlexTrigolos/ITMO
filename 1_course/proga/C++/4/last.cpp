#include <iostream>
#include <vector>
#include "last.h"

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
    vector<Figure> figures;
	//vector <Ellipse> ell;
	do{
		print_menu();
		var = take_variant();
		switch(var){
			case 1:
				cout << "1. Triangle\n2. Ellipse" << endl;
				cin >> a;
				if(a == 1){
					Figure fig;
					figures.push_back(fig);
					//Triangle triangle();
					//tri.push_back(triangle);
				}/*else{
					cout << "height = ";
					cin >> a;
					cout << "width = ";
					cin >> b;
					Ellipse ellipse(a, b);
					ell.push_back(ellipse);
				}*/
				break;
			case 2:
			
				break;
			case 3:
			
				break;
			case 4:
			
				break;
			case 5:
				
				break;
			case 6:
			
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