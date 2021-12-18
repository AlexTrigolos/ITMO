#ifndef _2_H
#define _2_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DO{
	private:
	string file_name;
	int a;
	double b;
	string str;
	ofstream out;
	
	public:
	
	DO(){
		file_name = "123.txt";
	}
	
	void open(){
		out.open(file_name);
		if(out.is_open()){
			cout << "OPEN\n";
		}else{
			cout << "CLOSE\n";
		}
		
	}
	
	void close(){
		out.close();
		if(out.is_open()){
			cout << "OPEN\n";
		}else{
			cout << "CLOSE\n";
		}
	}
	
	void name(){
		cout << file_name << "\n";
	}
	
	void is_on(){
		if(out.is_open()){
			cout << "OPEN\n";
		}else{
			cout << "CLOSE\n";
		}
		
	}
	
	void writes(){
		cout << "Give me a string" << endl;
		cin >> str;
		out << str;
	}

	void writei(){
		cout << "Give me a integer" << endl;
		cin >> a;
		out << a;
	}
	
	void writev(){
		cout << "Give me a real number" << endl;
		cin >> b;
		out << b;
	}
	
	
};
#endif