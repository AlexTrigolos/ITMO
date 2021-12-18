#pragma once
#include <iostream>
#include <Math.h>

using namespace std;

class Vector2D{
public:
double x, y;
};

class PhysObject{
	public:
	double mass_ = 1;
	double mass(){
		return mass_;
	}
};

// Интерфейс "Физический объект".
class IPhysObject {
public:
// Масса, кг.
virtual double mass() = 0;
// Координаты центра масс, м.
virtual Vector2D position() = 0;
// Сравнение по массе.
virtual bool operator== (PhysObject& ob ) const = 0;
// Сравнение по массе.
virtual bool operator< ( PhysObject& ob ) const = 0;
};

// Интерфейс для классов, которые можно задать через диалог с пользователем.
class IDialogInitiable {
// Задать параметры объекта с помощью диалога с пользователем.
virtual void initFromDialog() = 0;
};

// Интерфейс "Геометрическая фигура".
class IGeoFig {
public:
// Площадь.
virtual double square() = 0;
// Периметр.
virtual double perimeter() = 0;
};

// Интерфейс "Отображаемый"
class IPrintable {
public:
// Отобразить на экране
// (выводить в текстовом виде параметры фигуры).
virtual void draw() = 0;
};

// Вектор
class CVector2D {
public:
double x, y;
};

// Интерфейс "Класс"
class BaseCObject {
public:
// Имя класса (типа данных).
virtual const char* classname() = 0;
// Размер занимаемой памяти.
virtual unsigned int size() = 0;
};

class Triangle : public IGeoFig, public BaseCObject, public IPrintable, public CVector2D, public IDialogInitiable, public IPhysObject, public PhysObject{
	private:
	double side;
	const char* name = "triangle";
	unsigned int siz = sizeof(Triangle);
	//double mas = 1;
	public:
	Triangle(double s){
		this->side = s;
		this->x = 0;
		this->y = 0;
	}
	double square() override{
		return sqrt(3) * side * side / 4;
	}
	double perimeter() override{
		return 3 * side;
	}
	const char* classname() override{
		return this->name;
	}
	unsigned int size() override{
		return this->siz;
	}
	void draw(){
		cout << "square = " << this->square() << ", perimeter = " << this->perimeter() << ", side = " << this->side << ".\n";
	}
	void initFromDialog() override{
		cout << "Enter center of figure - x and y and mass of figure.\n";
		cin >> this->x >> this->y >> this->mass_;
	}
	double mass() override{
		return mass_;
	}
	Vector2D position() override{
		Vector2D abc;
		abc.x = this->x;
		abc.y = this->y;
		return abc;
	}
	bool operator== ( PhysObject& ob ) const override{
		return (this->mass_ == ob.mass());
	}
	bool operator< ( PhysObject& ob ) const override{
		return (this->mass_ < ob.mass());
	}
};

class Ellipse : public IGeoFig, public BaseCObject, public IPrintable, public CVector2D, public IDialogInitiable{
	private:
	double height;
	double width;
	const char* name = "ellipse";
	unsigned int siz = sizeof(Ellipse);
	double mas = 1;
	public:
	Ellipse(double h, double w){
		this->width = w;
		this->height = h;
		this->x = 0;
		this->y = 0;
	}
	double square() override{
		return M_PI * width * height / 4;
	}
	double perimeter() override{
		return 2 * M_PI * sqrt((width / 2 * width / 2 + height / 2 * height / 2) / 2);
	}
	const char* classname() override{
		return this->name;
	}
	unsigned int size() override{
		return this->siz;
	}
	void draw() override{
		cout << "square = " << this->square() << ", perimeter = " << this->perimeter() << ", height = " << this->height << ", width = " << this->width << ".\n";
	}
	void initFromDialog() override{
		cout << "Enter center of figure - x and y and mass of figure.\n";
		cin >> this->x >> this->y;
	}
};