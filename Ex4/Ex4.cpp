#include <iostream>
#include "Words.h"

void printTxtFile(std::string path)
{
	std::string getcontent;
	std::ifstream openfile(path);
	if (openfile.is_open())
	{
		while (std::getline(openfile, getcontent))
		{
			std::cout << getcontent << std::endl;
		}
	}
	std::cout << "\n";
}

void main(int argc, char* argv[])
{
		
	try
	{	
		//SizeOfUndo ReplacementMode== Patches
		//5 0 path
		if (argc < 4)
		{
			std::cout << "Error. Few input parameters\n";
			return;
		}


		int numberOfUndo = std::atoi(argv[1]);
		Words::TypeOfReplacement mode = std::atoi(argv[2])!=0? Words::TypeOfReplacement::Learning : Words::TypeOfReplacement::Auto;

		Words dic(numberOfUndo);
		for (int i = 3; i < argc; ++i)
		{
			std::cout << "Input:\n";
			printTxtFile(argv[i]);

			dic.wordsReplace(argv[i], mode);
			std::cout <<"Result:\n";
			printTxtFile(argv[i]);

			dic.undo();
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
}

