#include "Expression.h"
std::map<std::string, float> Expression::variables;
std::map <std::string, std::pair<std::string, std::set<std::string>>> Expression::methods;

void Expression::execute(std::string commands)
{
	std::ifstream in(commands);
	if (!in.is_open()) throw std::logic_error("File is not open");


	std::string line;

	while (std::getline(in, line))
	{

		if (line.find("(") > 0 && line.find("):") != std::string::npos)
		{
			appendMethodsFromString(&line);
			continue;
		}

		if (line.find("(") > 0 && line.find(")=") != std::string::npos)
		{
			try
			{
				appendVariablesFromString(&line);
			}
			catch (std::exception e)
			{
				throw;
			}
			continue;
		}

		if (line.find('=') != std::string::npos)
		{
			std::string name, cmd;
			getAssignmentExpressionFromString(&line, &name, &cmd);
			try
			{
				variables[name] = calculateExpression(cmd);
			}
			catch (const std::exception e)
			{
				throw;
			}
			continue;
		}

		if (line.find("print") != std::string::npos)
		{
			try
			{
				startfuncPrint(line);
			}
			catch (const std::exception& e)
			{
				throw;
			}

			continue;
		}
	}
}


void Expression::appendVariablesFromString(std::string const * line)
{
	std::stringstream ss;
	std::string name;
	bool recorded = false;

	for (auto c : *line)
	{

		if (!recorded && c == '(')
		{
			name = ss.str();
			ss.str("");
			continue;
		}
		if (!recorded && c == '=')
		{
			recorded = true;
			ss.str("");
			continue;
		}
		if (c == ';')
		{
			break;
		}

		ss << c;
	}

	try
	{
		variables[name] = std::stof(ss.str());
	}
	catch (const std::exception)
	{
		throw std::logic_error("Invalid argument");
	}
}

void Expression::appendMethodsFromString(std::string const *line)
{
	std::stringstream ss;
	std::string name;
	bool variablesRecordMode = false;
	bool recorded = false;

	for (auto c : *line)
	{

		if (!recorded && c == '(')
		{
			name = ss.str();
			ss.str("");
			variablesRecordMode = true;
			continue;
		}
		if (!recorded && c == ',' && variablesRecordMode)
		{
			methods[name].second.insert(ss.str());
			ss.str("");
			continue;
		}
		if (!recorded && c == ')')
		{
			methods[name].second.insert(ss.str());
			ss.str("");
			variablesRecordMode = false;
			continue;
		}
		if (!recorded && c == ':')
		{
			recorded = true;
			ss.str("");
			continue;
		}
		if (c == ';')
		{
			break;
		}

		ss << c;
	}

	methods[name].first = ss.str();
}


void Expression::getAssignmentExpressionFromString(std::string const *line, std::string* name, std::string* calc)
{
	std::stringstream ss;
	bool recorded = false;

	for (auto c : *line)
	{
		if (!recorded && c == '=')
		{
			*name = ss.str();
			ss.str("");
			recorded = true;
			continue;
		}
		if (c == ';')
		{
			break;
		}

		ss << c;
	}

	*calc = ss.str();;
}


float Expression::calculateExpression(std::string cmd)
{
	std::cout << "CalculateExpression: " << cmd << "\n";

	size_t inside = false;
	std::vector<float> numbers;
	std::vector<char> operations;
	std::stringstream ss;


	//если есть внешние скобки то убрать
	size_t count = 0;
	for (auto c : cmd)
	{
		if (c == '(')
		{
			++inside;
			continue;
		}
		if (c == ')')
		{
			--inside;
			continue;
		}
		if (inside == 0) ++count;
	}

	if (count == 0 && cmd[0] == '(' && cmd[cmd.size() - 1] == ')')
	{
		cmd = cmd.substr(1, cmd.size() - 2);
	}

	//вычислить. разбиваем всё на нашей глубине по операндам и отправляем на вычисление конкретных операндов
	//результирующее значение сохраняем в один массив. операнд в другой
	for (auto c : cmd)
	{
		if (c == '(')
		{
			++inside;
		}
		if (c == ')')
		{
			--inside;
		}

		if (inside == 0 && (c == '*' || c == '/' || c == '+' || c == '-'))
		{
			operations.push_back(c);
			float val;
			//отправка операнда на вычисление
			try { val = calculateOperand(ss.str()); }
			catch (const std::exception& e) { throw; }
			numbers.push_back(val);

			ss.str("");
			continue;
		}

		ss << c;
	}

	try { numbers.push_back(calculateOperand(ss.str())); }
	catch (const std::exception& e) { throw; }

	//собираем результат
	float first, second;
	for (int i = 0; i < operations.size(); i++)
	{
		if (operations.at(i) == '*' || operations.at(i) == '/')
		{
			first = numbers.at(i);
			second = numbers.at(i + 1);
			numbers.at(i) = applyOperation(first, second, operations.at(i));
			numbers.erase(std::next(numbers.begin(), i + 1));
		}
	}

	for (int i = 0; i < operations.size(); i++)
	{
		if (operations.at(i) == '*' || operations.at(i) == '/')
		{
			operations.erase(std::next(operations.begin(), i));
		}
	}

	for (int i = 0; i < operations.size(); i++)
	{
		if (operations.at(i) == '+' || operations.at(i) == '-')
		{
			first = numbers.at(i);
			second = numbers.at(i + 1);
			numbers.at(i) = applyOperation(first, second, operations.at(i));
			numbers.erase(std::next(numbers.begin(), i + 1));
		}
	}


	std::cout << "Result: " << numbers.at(0) << "\n";
	return numbers.at(0);

}


float Expression::calculateOperand(std::string cmd)
{

	//если число то вернуть
	if (isNumber(cmd))
	{
		return atof(cmd.c_str());
	}


	//если это не число и скобок нет - значит это переменная. получить значение переменной и вернуть его
	if (cmd.find('(') == std::string::npos && cmd.find(')') == std::string::npos)
	{
		try
		{
			return getVariableValue(cmd);
		}
		catch (const std::exception& e)
		{
			throw;
		}

	}

	//если скобки по краям значит это подвыражение. отправить в рекусию
	if (cmd[0] == '(' && cmd[cmd.size() - 1] == ')')
	{
		try
		{
			return calculateExpression(cmd);
		}
		catch (const std::exception& ex) { throw; }
	}

	//скобки не по краям и по операндам не разбилось, значит что-то стоит вплотную к скобкам
	//значит маска такая:  afewsymbols(...). А это маска функции.
	//считываем функцию и отправляем на вычисление
	//
	//Обрабатываем неверную маску функции afewsymbols(...)asd или (...)asd
	if (cmd[cmd.size() - 1] != ')') throw std::logic_error("Incorrect expression");

	std::string name;
	std::vector<std::string> replacement;
	getFunctionData(&cmd, &name, &replacement);

	std::string res;
	try
	{   //подмена переменных
		res = getMethodReplacement(&name, &replacement);
	}
	catch (const std::exception& e) { throw; }

	try
	{   //вычисление результирующего выражения после подмены
		return calculateExpression(res);
	}
	catch (const std::exception& ex) { throw; }
}

void Expression::getFunctionData(std::string const * cmd, std::string* name, std::vector<std::string>* replacement)
{
	std::stringstream ss;
	bool isNameRecorded = false;
	size_t depth = 0;

	for (auto c : *cmd)
	{
		if (c == ')') --depth;
		if (c == '(')
		{
			++depth;
			if (isNameRecorded == false)
			{
				isNameRecorded = true;
				*name = ss.str();
				ss.str("");
				continue;
			}
		}

		if (isNameRecorded && (c == ',' || (c == ')' && depth == 0)))
		{
			try
			{
				//нашли переменную. отправим в рекусию на предварительное получение результата
				//например: func(ab+bc, 4). Сначала вычислится ab+bc. затем уже произойдет отправка в функцию.
				replacement->push_back(std::to_string(calculateExpression(ss.str())));
			}
			catch (const std::exception& ex) { throw; }
			ss.str("");
			continue;
		}

		ss << c;
	}
}


std::string Expression::getMethodReplacement(std::string* name, std::vector<std::string>* replacement)
{
	//подмена переменных в функции на значения
	std::pair<std::string, std::set<std::string>> methodValues;
	try
	{
		methodValues = getMethodValue(*name);
	}
	catch (const std::exception& e)
	{
		throw;
	}
	std::string result = methodValues.first;
	std::set<std::string>* original = &methodValues.second;
	std::stringstream ss, finalFunction;

	if (original->size() != replacement->size())
		throw std::logic_error("Incorrect function arguments");

	for (auto& c : result)
	{

		if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')
		{
			finalFunction << getVariableReplacement(ss.str(), original, replacement);
			finalFunction << c;
			ss.str("");
		}
		else
		{
			ss << c;
			if (&c == &result.back())
				finalFunction << getVariableReplacement(ss.str(), original, replacement);
		}
	}

	return finalFunction.str();
}


std::string Expression::getVariableReplacement(std::string val, std::set<std::string>* original, std::vector<std::string>* replacement)
{
	int i = 0;
	for (auto x : *original)
	{
		if (x == val) return replacement->at(i);
		++i;
	}

	return val;
}
















float Expression::getVariableValue(std::string str)
{

	float v;
	try 
	{
		v = variables[str];
	}
	catch (const std::exception& e)
	{
		throw std::logic_error("Variables is not exist");
	}
	return v;
}

std::pair<std::string, std::set<std::string>> Expression::getMethodValue(std::string name)
{
	std::pair<std::string, std::set<std::string>> v;
	try
	{
		v = methods[name];
	}
	catch (const std::exception& e)
	{
		throw std::logic_error("Method is not exist");
	}
	return v;
}



void Expression::startfuncPrint(std::string line)
{
	std::stringstream ss;
	ss << line;
	std::getline(ss, line, ' ');
	if (line == "print;")
	{
		printVariables();
	}
	else
	{
		std::getline(ss, line, ' ');
		if (line.find(";") != std::string::npos) 
			line=line.substr(0, line.size() - 1);
		try
		{
			std::cout << getVariableValue(line) << "\n";
		}
		catch (const std::exception& e)
		{
			throw;
		}

		
	}	
}


void Expression::printMethods()
{
	std::cout << "Methods:\n";
	for (auto x : methods)
	{
		std::cout << "Name: " << x.first <<"; Variables: ";
		for (auto y: x.second.second)
		{
			std::cout << y <<" ";
		}
		std::cout << "; Text: ";
		std::cout << x.second.first << "\n";
	}
	std::cout << "\n";
}

void Expression::printVariables()
{
	std::cout << "Variables: ";
	for (auto x : variables)
	{
		std::cout << x.first << "=" << x.second<<"; ";
	}
	std::cout << "\n";
}



bool Expression::isNumber(const std::string& s)
{
	for (auto c : s)
	{
		if (!(isdigit(c) || c == '.')) return false;
	}
	return true;
}

float Expression::applyOperation(float a, float b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	default: return 0;
	}
}