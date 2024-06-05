#include <iostream>
#include "Messages.h"

int main()
{
    std::string path = "C:\\Users\\lifem\\iCloudDrive\\Documents\\Учеба\\Языки и методы\\Курсовая работа\\CourseWork_S4\\Ex12\\Input.txt";
    std::set<Messages::message>  data;
    Messages::Load(path, &data);

    std::cout << "All messages:\n";
    Messages::printMessages(&data);

    std::cout << "\nMessage from username:\n";
    Messages::printUserMessages("Username", & data);

    std::cout << "\nAll message from 08.10.2015 to 02.11.2015:\n";
    Messages::printMessagesFromInterval(Messages::ConvertToDate(2015, 10, 8), 
        Messages::ConvertToDate(2015, 11, 2),  Messages::ConvertToTime(9, 0, 0, 0), 
        Messages::ConvertToTime(9, 0, 0, 0), &data);

    std::cout << "\nAll message from username from 08.10.2015 to 02.11.2015:\n";
    Messages::printUserMessagesFromInterval("Username", Messages::ConvertToDate(2015, 10, 8), 
        Messages::ConvertToDate(2015, 11, 2), Messages::ConvertToTime(9, 0, 0, 0), 
        Messages::ConvertToTime(9, 0, 0, 0), &data);

    Messages::removeMessage(&data, data.begin());
    Messages::removeUser("Parrot", &data);
    std::cout << "\nAll messages after remove:\n";
    Messages::printMessages(&data);

}
