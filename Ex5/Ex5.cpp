#include <iostream>
#include "Work.h"
int main()
{
	std::string path = "C:\\Users\\lifem\\iCloudDrive\\Documents\\Учеба\\Языки и методы\\Курсовая работа\\CourseWork\\Ex5\\Input.txt";
	auto data = Work::Load(path);

	auto deal = Work::getDearestDeal("FirstName LastName ParentName", &data);
	std::cout << "Dearest Deal : \n";
	Work::printDeal(deal);

	auto deal1 = Work::getLongestDeal("FirstName LastName ParentName", &data);
	std::cout << "\nLongest Deal:\n";
	Work::printDeal(deal1);

	auto s = Work::getSumSalary("FirstName LastName ParentName", &data);
	std::cout << "\nSum salary: " << s <<"\n";

	std::cout << "\nWorker deal list:\n";
	Work::printDealList("FirstName2 LastName ParentName", &data);

	Work::RemoveEmployee("FirstName2 LastName ParentName", &data);
	std::cout << "\nWorker deal list after remove worker:\n";
	Work::printDealList("FirstName2 LastName ParentName", &data);

}

