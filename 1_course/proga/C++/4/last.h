#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Vector2D{
public:
	double x, y;
};

// Интерфейс "Физический объект".
class IPhysObject {
public:
// Масса, кг.
virtual double mass() = 0;
// Координаты центра масс, м.
virtual Vector2D position() = 0;
// Сравнение по массе.
//virtual bool operator== (const IPhysObject &obj) const = 0;
// Сравнение по массе.
//virtual bool operator< (const IPhysObject &obj) const = 0;
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

class Figure : public IDialogInitiable/*, public BaseCObject, public IGeoFig, public IPhysObject, public IPrintable*/{
	protected:
    double length_;
    double width_;
    int mass_;
    CVector2D position_;
	
public:
    BaseFigure();
    double length(){
		return length_;
	};
    double width();
    void initFromDialog()override;
    /*double square() override;
    double perimeter() override;
    double mass() const override;
    CVector2D position() override;
    bool operator == (const IPhysObject &obj) const override;
    bool operator < (const IPhysObject &obj) const override;
    void draw() override;
    const char* classname() override;
    unsigned int size() override;*/
};


class Triangle: Figure {
	public:
	Triangle(){
		initFromDialog();
	}
		void initFromDialog(){
			/*std::cout << "Triangle" << std::endl;
			std::cout << "Enter 3 points (x, y)" << std::endl;
			std::cout << "Enter x, y with space for 1st point: ";
			CVector2D point1;
			std::cin >> point1.x >> point1.y;
			std::cout << "Enter x, y with space for 2nd point: ";
			CVector2D point2;
			std::cin >> point2.x >> point2.y;
			std::cout << "Enter x, y with space for 3rd point: ";
			CVector2D point3;
			std::cin >> point3.x >> point3.y;
			std::cout << "Enter mass of triangle: ";
			int mass;
			std::cin >> mass;
			width_ = sqrt(pow(abs(point3.x - point1.x), 2) + pow(abs(point3.y - point1.y), 2));
			length_ = width_ * sqrt(3) / 2;
			mass_ = mass;
			position_.x = ((point1.x + point2.x + point3.x) * 1.0) / 3;
			position_.y = ((point1.y + point2.y + point3.y) * 1.0) / 3;*/
		}
};

