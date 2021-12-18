#include <iostream>

#include "Section.h"



Section::Section()

{

    Section::initFromDialog();

}

void Section::initFromDialog()

{

    // Ввод отрезка

    CVector2D st; // Start

    CVector2D fn; // Finish



    std::cout << "Section" << std::endl;

    std::cout << "Enter 2 points (x, y)" << std::endl;



    std::cout << "Enter x, y with space for 1st point: ";

    std::cin >> st.x >> st.y;



    std::cout << "Enter x, y with space for 2nd point: ";

    std::cin >> fn.x >> fn.y;



    std::cout << "Enter mass of section: ";

    int mass;

    std::cin >> mass;



    length_ = std::abs(st.x - fn.x) + std::abs(st.y - fn.y);

    width_ = 0; // Default

    mass_ = mass;



    if (st.x - fn.x) //

    {

    position_.x = ((st.x + fn.x) * 1.0) / 2;

    position_.y = st.y;

    }

    else if (st.y - fn.y)

    {

    position_.x = st.x;

    position_.y = ((st.y + fn.y) * 1.0) / 2;

    }

}