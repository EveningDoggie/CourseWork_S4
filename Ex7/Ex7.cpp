
#include <iostream>
#include "Expression.h"

int main()
{
    try
    {
        Expression::execute("C:\\Users\\lifem\\iCloudDrive\\Documents\\Учеба\\Языки и методы\\Курсовая работа\\CourseWork\\Ex7\\Input.txt");
    }
    catch (std::exception e)
    {
        std::cout << e.what();
    }
}

