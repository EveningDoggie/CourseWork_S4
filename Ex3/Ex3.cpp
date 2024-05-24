// Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Person.h"

int main()
{
    srand(time(0));
    auto p = Person::Person(Person::CharacterType::defender);
    std::cout << "Person generated. \n";

     p.printStats();
     std::cout <<"\nHit without armour: "<< p.doHit() <<"\n";
     std::cout << "Hit without armour: " << p.doHit() << "\n";
     std::cout << "Hit without armour: " << p.doHit() << "\n";
     std::cout << "Hit without armour: " << p.doHit() << "\n";
     std::cout << "Hit without armour: " << p.doHit() << "\n\n";
     
     p.generateEquipments();
     p.printEquipments();
     std::cout << "\nHit with armour: " << p.doHit() << "\n";
     std::cout << "Hit with armour: " << p.doHit() << "\n";
     std::cout << "Hit with armour: " << p.doHit() << "\n";
     std::cout << "Hit with armour: " << p.doHit() << "\n";
     std::cout << "Hit with armour: " << p.doHit() << "\n";


}
