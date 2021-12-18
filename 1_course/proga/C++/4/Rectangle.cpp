#include <iostream>
#include <cmath>
#include "Rectangle.h"

Rectangle::Rectangle() {
    Rectangle::initFromDialog();
}

void Rectangle::initFromDialog() {
    // Ввод с клавиатуры
    // Параметры ввода: вводить точки последовательно, например:
    // A(2, 2), B(4, 2), C(4, 4), D(2, 4)
    std::cout << "Rectangle" << std::endl;
    std::cout << "Enter 4 points (x, y)" << std::endl;
    std::cout << "Enter x, y with space for 1st point: ";
    CVector2D point1;
    std::cin >> point1.x >> point1.y;
    std::cout << "Enter x, y with space for 2nd point: ";
    CVector2D point2;
    std::cin >> point2.x >> point2.y;
    std::cout << "Enter x, y with space for 3rd point: ";
    CVector2D point3;
    std::cin >> point3.x >> point3.y;
    std::cout << "Enter x, y with space for 4th point: ";
    CVector2D point4;
    std::cin >> point4.x >> point4.y;
    std::cout << "Enter mass of rectangle: ";
    int mass;
    std::cin >> mass;
    length_ = sqrt(pow(abs(point2.x - point1.x), 2) + pow(abs(point2.y - point1.y), 2));
    width_ = sqrt(pow(abs(point4.x - point1.x), 2) + pow(abs(point4.y - point1.y), 2));
    mass_ = mass;
    position_.x = ((point1.x + point2.x) * 1.0) / 2;
    position_.y = ((point1.y + point4.y) * 1.0) / 2;
}