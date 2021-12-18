#ifndef _2_1_H
#define _2_1_H
#include <iostream>
#include <string>
#include "2_1.h"

using namespace std;

class Menu{
	private:
	DO rar;
	int var;
	void print_menu(){
		system("cls");
		cout << "What do you want to do?" << endl;
		cout << "1. Open file." << endl;
		cout << "2. Close file." << endl;
		cout << "3. Gett the file name." << endl;
		cout << "4. Check whether a file is open." << endl;
		cout << "5. Write a string to a file." << endl;
		cout << "6. Write an integer to a file." << endl;
		cout << "7. Write a real number to a file." << endl;
		cout << "8. Exit." << endl;
	}

	int take_variant(){
		int s;
		cin >> s;
		return s;
	}
	
	public:
	int start(){
		do{
			print_menu();
			var = take_variant();
			switch(var){
				case 1:
					rar.open();
					break;
					
				case 2:
					rar.close();
					break;
					
				case 3:
					rar.name();
					break;
					
				case 4:
					rar.is_on();
					break;
					
				case 5:
					rar.writes();
					break;
					
				case 6:
					rar.writei();
					break;
					
				case 7:
					rar.writev();
					break;
			}
			if(var != 8){
				system("pause");
			}
		}while(var != 8);
		
		return 0;
	}
};
#endif