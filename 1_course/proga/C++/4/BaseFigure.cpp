#include "BaseFigure.h"
#include <iostream>
#include <typeinfo>

BaseFigure::BaseFigure() {}

BaseFigure::BaseFigure(int length, int width, int mass, CVector2D vector2D)
        : length_(length)
        , width_(width)
        , mass_(mass)
        , position_(vector2D) {}

double BaseFigure::length()
{
    return length_;
}

double BaseFigure::width()
{
    return width_;
}

double BaseFigure::square()
{
    return length_ * width_;
}

double BaseFigure::perimeter()
{
	return 2 * (length_ + width_);
}

double BaseFigure::mass() const
{
    return mass_;
}

CVector2D BaseFigure::position()
{
    return position_;
}

void BaseFigure::initFromDialog() {}

bool BaseFigure::operator == (const IPhysObject &obj) const
{
    return mass() == obj.mass();
}

bool BaseFigure::operator < (const IPhysObject &obj) const
{
    return mass() < obj.mass();
}

void BaseFigure::draw()
{
    std::cout << "Width: " << width() << std::endl;
    std::cout << "Length: " << length() << std::endl;
    std::cout << "Square: " << square() << std::endl;
    std::cout << "Perimeter: " << perimeter() << std::endl;
    std::cout << "Mass: " << mass() << std::endl;
    std::cout << "Position: x = " << position().x << ", y = " << position().y << std::endl;
    std::cout << "Class name: " << classname() << std::endl;
    std::cout << "Size: " << size() << std::endl;
}

const char* BaseFigure::classname()
{
    return typeid(*this).name();
}

unsigned int BaseFigure::size()
{
    return sizeof(*this);
}