#include <iostream>
#include "Arrays.h"
using namespace std;

int main()
{

    int* A = new int(1);
    int* B = new int(1);
    size_t sizea=0, sizeb=0;
    srand(time(0));
    string pathload = "C:\\Users\\lifem\\iCloudDrive\\Documents\\Учеба\\Языки и методы\\Курсовая работа\\CourseWork\\Ex2\\Load.txt";
    string pathsave = "C:\\Users\\lifem\\iCloudDrive\\Documents\\Учеба\\Языки и методы\\Курсовая работа\\CourseWork\\Ex2\\Save.txt";

    Arrays::Load(&A, pathload);
    Arrays::Rand(&B, 6, 1, 10);
    Arrays::Save(A, pathsave);
    std::cout << "Load A: "; Arrays::Print(A);
    std::cout << "Rand B: "; Arrays::Print(B);
    Arrays::Concat(&A, B);
    std::cout << "Concat A, B: "; Arrays::Print(A);
    Arrays::Remove(&A, 2, 4);
    std::cout << "Remove A: "; Arrays::Print(A);
    Arrays::Copy(&A, B, 1, 5);
    std::cout << "Copy A: ";  Arrays::Print(A);
    Arrays::Permute(&A);
    std::cout << "Permute A: "; Arrays::Print(A);
    Arrays::Sort(&A, true);
    std::cout << "Sort A: "; Arrays::Print(A);
    Arrays::Load(&A, pathload);
    std::cout << "Load A: "; Arrays::Print(A);
    std::cout << "Intersect A and B: ";
    Arrays::Intersect(&A, B); Arrays::Print(A);
    Arrays::Load(&A, pathload);
    Arrays::Xor(&A, B);
    std::cout << "Xor A and B: "; Arrays::Print(A);
    Arrays::Load(&A, pathload);
    std::cout << "\nStat A: "; Arrays::Stat(A);
    Arrays::Free(&A);
    std::cout << "\nFree A: "; Arrays::Print(A);

}
