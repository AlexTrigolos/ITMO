#ifndef _3_H
#define _3_H
#include <iostream>
#include <Math.h>

using namespace std;

class Point{
public:
	double x;
	double y;
	Point(){
		this->x = 0;
		this->y = 0;
	}
	Point(double a, double b){
		this->x = a;
		this->y = b;
	}
	Point operator*(double& one){
		Point temp;
		temp.x = this->x * one;
		temp.y = this->y * one;
		return temp;
	}
	Point operator+(const Point& other){
		Point temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		return temp;
	}
	Point operator*(const Point& other){
		Point temp;
		temp.x = this->x * other.x;
		temp.y = this->y * other.y;
		return temp;
	}
	operator double(){
		return sqrt(this->x * this->x + this->y * this->y);
	}
};

class Stack{
public:
	struct List{
		int value;
		List* next;
	};
	List* top = nullptr;
	void push(int num){
		List* now = new List();
		now->value = num;
		now->next = top;
		top = now;
	}
	void pop(){
		cout << top->value << "\n";
		top = top->next;
	}
	Stack operator<<(int num){
		push(num);
		return *this;
	}
	Stack operator>>(int num){
		pop();
		return *this;
	}
	void display(){
		List* now = new List();
		now = top;
		while(now != nullptr){
			if(now->next != nullptr)
				cout << now->value << " ";
			else
				cout << now->value << endl;
			now = now->next;
		}
	}
	
};
#endif