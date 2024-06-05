#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>

class Expression
{
private:

	typedef struct variable
	{
		std::string name;
		float value;
	};

	~Expression();

	static std::list<variable*> variables;
	static float getVariableValue(std::string str);
	static float applyOperation(float a, float b, char op);
	static bool isNumber(const std::string& s);
	static float calculateOperand(std::string cmd);
	static float calculateExpression(std::string cmd);
	static void getAssignmentExpressionFromString(std::string line, std::string* name, std::string* calc);
	static void startfuncPrint(std::string line);
	static bool setVariableValue(std::string name, float value);
	static void disposeVariableFromName(std::string name);
	static void disposeVariable(variable * v);
	static void disposeVariableFromBack(size_t count);
public:

	static void execute(std::string path);
	static void executeCommands(std::string const cmd);
	static void printVariables();


};
