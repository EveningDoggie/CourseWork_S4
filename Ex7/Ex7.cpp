
#include <iostream>
#include "Expression.h"

int main()
{
    try
    {
        Expression::execute("C:\\Users\\lifem\\iCloudDrive\\Documents\\Учеба\\Языки и методы\\Курсовая работа\\CourseWork_S4\\Ex7\\Input.txt");
    }
    catch (std::exception e)
    {
        std::cout << e.what();
    }
}

