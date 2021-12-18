#include <iostream>
#include <vector>
#include <algorithm>
#include "BaseFigure.h"
#include "Rectangle.h"
#include "Section.h"
#include "Triangle.h"

void Menu()
{
    std::cout << "\nEnter 1 to add Rectangle to vector" << std::endl;
    std::cout << "Enter 2 to add Section to vector" << std::endl;
    std::cout << "Enter 3 to show all figures" << std::endl;
    std::cout << "Enter 4 to show sum of all squares" << std::endl;
    std::cout << "Enter 5 to show sum of all perimeters" << std::endl;
    std::cout << "Enter 6 to show all positions" << std::endl;
    std::cout << "Enter 7 to show memory size" << std::endl;
    std::cout << "Enter 8 to show mass sorted vector of figures" << std::endl;
    std::cout << "Enter 0 to exit program\n" << std::endl;
}

int main()
{
    std::vector<BaseFigure*> figures;
    int k = 0;
    Menu();
    std::cout << "Your command: ";
    int cmd;
    std::cin >> cmd;
    while (cmd)
    {
        if (cmd == 1)
        {
            figures.push_back(new Rectangle());
        }
        else if (cmd == 2)
        {
            figures.push_back(new Triangle());
        }
        else if (cmd == 3)
        {
            std::cout << "\nALL FIGURES DESCRIPTION: " << std::endl;
            for (int i = 0; i < figures.size(); i++)
            {
                std::cout << std::endl;
                figures[i]->draw();
                std::cout << std::endl;
            }
            std::cout << "END OF DESCRIPTION\n" << std::endl;
        }
        else if (cmd == 4)
        {
            int sum = 0;
            for (int i = 0; i < figures.size(); i++)
            {
                sum += figures[i]->square();
            }
            std::cout << "Sum of squares: " << sum << std::endl;
        }
        else if (cmd == 5)
        {
            int sum = 0;
            for (int i = 0; i < figures.size(); i++)
            {
                sum += figures[i]->perimeter();
            }
            std::cout << "Sum of perimeters: " << sum << std::endl;
        }
        else if (cmd == 6)
        {
            for (int i = 0; i < figures.size(); i++)
            {
                std::cout << "Position of #" << i + 1 << " figure is: {" << figures[i]->position().x << ", " <<
							figures[i]->position().y << "}" << std::endl;
            }
        }
        else if (cmd == 7)
        {
            int memory = 0;
            for (int i = 0; i < figures.size(); i++)
            {
                memory += figures[i]->size();
            }
            std::cout << "Summary memory: " << memory << std::endl;
        }
        else if (cmd == 8)
        {
            std::sort(figures.begin(), figures.end());
            for (int i = 0; i < figures.size(); i++)
            {
                std::cout << "#" << i + 1 << " figure description: " << std::endl;
                figures[i]->draw();
            }
        }
        else
        {
            std::cout << "Unknown command, try again!" << std::endl;
        }
        k++;
        if (k % 3 == 0)
        {
            Menu();
        }
        std::cout << "Your command: ";
        std::cin >> cmd;
    }
    return 0;
}