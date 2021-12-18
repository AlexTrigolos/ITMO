#include <iostream>
#include <cmath>
#include "Triangle.h"

Triangle::Triangle() {
    Triangle::initFromDialog();
}

void Triangle::initFromDialog() {
    // Ввод с клавиатуры
    // Параметры ввода: вводить точки последовательно, например:
    // A(2, 2), B(4, 2), C(4, 4), D(2, 4)
    std::cout << "Triangle" << std::endl;
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
	position_.y = ((point1.y + point2.y + point3.y) * 1.0) / 3;
}