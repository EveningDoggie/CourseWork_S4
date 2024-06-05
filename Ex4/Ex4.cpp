#include <iostream>
#include "Words.h"

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
			dic.wordsReplace(argv[i], mode);
			std::cout << argv[i] << " is writed\n";
			
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
}
