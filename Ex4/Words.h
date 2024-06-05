#pragma once
#include <iostream>
#include <fstream>

#include <string>
#include <map>
#include <vector>
#include <deque>

#include <sstream>

class Words
{
private:

	std::deque<std::pair<std::string, std::vector<std::string>> *> undodeque;

	std::map<std::string, std::string> words;

public:

	enum TypeOfReplacement
	{
		Learning,
		Auto
	};

	std::string _pathToDictionary = "./InputDictionary.txt";

	int _undoSize;

	Words(int undoSize);

	~Words();

	void wordsReplace(std::string path, TypeOfReplacement type);

	void saveDictionary(std::string pathToDictionary);

	void saveToDeque(std::string * path, std::vector<std::string> * vector);

	void undo();

	void printDictionary();

	std::string addValueToDictionary(std::string word);
};

