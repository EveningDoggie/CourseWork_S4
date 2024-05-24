#include "Expression.h"
#include <vector>
std::list<Expression::variable*> Expression::variables;


void Expression::execute(std::string path)
{
	std::ifstream in(path);
	if (!in.is_open()) throw std::logic_error("File is not open");
	std::stringstream ss;
	if (in) 
	{

		ss << in.rdbuf();
		in.close();
	}
	executeCommands(ss.str());
}

void Expression::executeCommands(std::string const cmd)
{
	std::string line;
	std::stringstream insideExpression;
	std::stringstream cmdss;
	cmdss << cmd;
	size_t depthExpression = 0;
	int varsCount = 0;

	while (std::getline(cmdss, line))
	{
		if (line.find('{') != std::string::npos)
		{
			++depthExpression;
			if(depthExpression==1) continue;
		}

		if (line.find('}') != std::string::npos)
		{
			--depthExpression;

			if (depthExpression == 0)
			{
				executeCommands(insideExpression.str());
				insideExpression.str("");
				continue;
			}
		}

		if (depthExpression!=0) 
		{
			insideExpression << line <<"\n";
			
		}
		else
		{
			if (line.find('=') != std::string::npos)
			{
				std::string name, cmd;
				//получить название переменной и к чему она приравнивается (выражение)
				getAssignmentExpressionFromString(line, &name, &cmd);
				try
				{
					//отправить выражение на вычисление и записать результат в переменную
					if(setVariableValue(name, calculateExpression(cmd)))
						++varsCount;
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

	disposeVariableFromBack(varsCount);

}


void Expression::getAssignmentExpressionFromString(std::string line, std::string* name, std::string* calc)
{
	//разбить строку на имя переменной и выражение к чему она приравнивается
	std::stringstream ss;
	bool recorded = false;

	for (auto c : line)
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
	//вычисление выражения
	std::cout << "CalculateExpression: " << cmd << "\n";

	size_t inside = false;
	std::vector<float> numbers;
	std::vector<char> operations;
	std::stringstream ss;

	//если стоят внешние скобки то убрать их
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

		//разбить выражение по операндам на текущей глубине скобок.
		//операции сохранить в массив. Выражение вычислить и сохранить в дпугой массив
		if (inside == 0 && (c == '*' || c == '/' || c == '+' || c == '-'))
		{
			operations.push_back(c);
			float val;
			try 
			{ 
				val = calculateOperand(ss.str()); 
			}
			catch (const std::exception& e) 
			{ 
				throw; 
			}
			numbers.push_back(val);

			ss.str("");
			continue;
		}

		ss << c;
	}

	try { numbers.push_back(calculateOperand(ss.str())); }
	catch (const std::exception& e) { throw; }



	std::cout << "Numbers: ";
	for (auto x : numbers)
	{
		std::cout << x << " ";
	}
	std::cout << "\n";
	std::cout << "Operations: ";
	for (auto x : operations)
	{
		std::cout << x << " ";
	}
	std::cout << "\n";


	//вычислить результат
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

	std::cout << "Result: " << numbers.at(0) << "\n\n";
	return numbers.at(0);

}

float Expression::calculateOperand(std::string cmd)
{
	//если это число то вернуть его
	if (isNumber(cmd))
	{
		return atof(cmd.c_str());
	}

	//если нет скобок  и не число значит переменная. получить значение и вернуть
	if (cmd.find('(') == std::string::npos 
		&& cmd.find(')') == std::string::npos)
	{

		try
		{
			if (isdigit(cmd.at(0))) throw std::logic_error("variable cannot start with a number");
			return getVariableValue(cmd);
		}
		catch (const std::exception& e)
		{
			throw;
		}

	}

	//если в начале скобки значит это подвыражение. отправить в рекурсию на вычисление
	if (cmd[0] == '(' && cmd[cmd.size() - 1] == ')')
	{
		try
		{
			return calculateExpression(cmd);
		}
		catch (const std::exception& ex) { throw; }
	}
}











void Expression::disposeVariableFromBack(size_t count)
{
	for (int i = 0; i < count; ++i)
	{
		disposeVariable(variables.back());
	}
}




void Expression::disposeVariable(variable * x)
{
	variables.remove(x);
	delete x;
}


void Expression::disposeVariableFromName(std::string name)
{
	for (auto x : variables)
	{
		if (x->name == name)
		{
			disposeVariable(x);
		}
		return;
	}
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
			line = line.substr(0, line.size() - 1);
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

float Expression::getVariableValue(std::string searchName)
{
	for (auto x : variables)
	{
		if (x->name == searchName)
			return x->value;
	}

	throw std::logic_error("Variables is not exist");
}

bool Expression::setVariableValue(std::string name, float value)
{
	for (auto x : variables)
	{
		if (x->name == name)
		{
			x->value = value;
			return false;
		}
	}

	variable* var = new variable();
	var->name = name;
	var->value = value;
	variables.push_back(var);
	return true;
}


Expression::~Expression()
{
	for (auto x : variables)
	{
		delete x;
	}
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


void Expression::printVariables()
{
	std::cout << "Variables: ";
	for (auto x : variables)
	{
		std::cout << x->name << "=" << x->value << "; ";
	}
	std::cout << "\n";
}


