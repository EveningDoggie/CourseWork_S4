#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <list>

class Expression
{
private:

	static size_t MAX_RAM;
	static size_t OCCUPIED_RAM;

	typedef struct variable
	{
		std::string name;
		void* ptr;
		bool canDispose = false;
		size_t size;
	};

	~Expression();

	static std::list<variable> variables;

	static variable getVariable(std::string searchName);
	static void addVariable(std::string name, void* ptr, size_t size);

	static float applyOperation(float a, float b, char op);
	static bool isNumber(const std::string& s);

	static void executeFunc(std::string cmd, std::string varname);
	static void getAssignmentExpressionFromString(std::string line, std::string* name, std::string* calc);
	static void getFuncExpressionFromString(std::string line, std::string* name, std::list<std::string>* variables);
	static void _showvar();
	static void* _new(size_t value);


	static void checkAsDisposeVariableFromBack(size_t count);

public:

	static void execute(std::string path, size_t maxram);
	static void executeCommands(std::string const cmd);
	static void printVariables();


};
