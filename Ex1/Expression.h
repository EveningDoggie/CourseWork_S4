#pragma once

#include <map>
#include <string>
#include <set>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


class Expression
{
private:

	static std::map <std::string, float> variables;
	static std::map <std::string, std::pair<std::string, std::set<std::string>>> methods;
	
	static float getVariableValue(std::string str);
	static std::pair<std::string, std::set<std::string>> getMethodValue(std::string str);
	static std::string getMethodReplacement(std::string *name, std::vector<std::string>* replacement);
	static std::string getVariableReplacement(std::string val, std::set<std::string>* original, std::vector<std::string>* replacement);
	static void getFunctionData(std::string const *str, std::string *name, std::vector<std::string>* replacement);
	static float applyOperation(float a, float b, char op);
	static bool isNumber(const std::string& s);
	static float calculateOperand(std::string cmd);
	static float calculateExpression(std::string cmd);
	static void startfuncPrint(std::string line);
	static void appendMethodsFromString(std::string const *line);
	static void appendVariablesFromString(std::string const *line);
	static void getAssignmentExpressionFromString(std::string const * line, std::string* name, std::string* calc);
public:
	
	static void execute(std::string cmd);
	static void printMethods();
	static void printVariables();
	

};
