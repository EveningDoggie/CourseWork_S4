#include "Expression.h"
std::list<Expression::variable> Expression::variables;
size_t Expression::MAX_RAM;
size_t Expression::OCCUPIED_RAM;


void Expression::execute(std::string path, size_t maxram)
{
	MAX_RAM = maxram;
	OCCUPIED_RAM = 0;
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
			if (depthExpression == 1) continue;
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

		if (depthExpression != 0)
		{
			insideExpression << line << "\n";
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
					//отправить выражение на вычисление
					try
					{
						executeFunc(cmd, name);
					}
					catch(std::exception e)
					{
						throw;
					}

					++varsCount;
				}
				catch (const std::exception e)
				{
					throw;
				}
				continue;
			}

			if (line.find("ShowVar") != std::string::npos)
			{
				try
				{
					_showvar();
				}
				catch (const std::exception& e)
				{
					throw;
				}
				continue;
			}
		}
	}

	checkAsDisposeVariableFromBack(varsCount);
}


void Expression::checkAsDisposeVariableFromBack(size_t count)
{
	size_t start = variables.size() - count;
	int i = 0;
	for (auto &x : variables)
	{
		if (i >= start)
		{
			x.canDispose = true;
		}
		++i;
	}
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


void Expression::executeFunc(std::string cmd, std::string varname)
{
	std::string name;
	std::list<std::string> variables;
	getFuncExpressionFromString(cmd, &name, &variables);
	if (name == "new")
	{
		size_t value;
		try
		{
			value = std::atoi(variables.begin()->c_str());
		}
		catch(std::exception e)
		{
			throw std::logic_error("incorrect arguments");
		}

		void* ptr;
		try
		{
			ptr = _new(value);
		}
		catch (std::exception e)
		{
			throw;
		}
		addVariable(varname, ptr, value);
	}
}

void Expression::getFuncExpressionFromString(std::string cmd, std::string* name, std::list<std::string>* variables)
{

	std::stringstream ss;
	bool isNameRecorded = false;
	size_t depth = 0;

	for (auto c : cmd)
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
				variables->push_back(ss.str());
			}
			catch (const std::exception& ex) { throw; }
			ss.str("");
			continue;
		}
		ss << c;
	}


}

void* Expression::_new(size_t value)
{
	if (OCCUPIED_RAM + value > MAX_RAM)
	{
		for (auto x : variables)
		{
			if (x.canDispose)
			{
				if(x.ptr!=nullptr) 
					delete x.ptr;
				x.ptr = nullptr;
				OCCUPIED_RAM -= x.size;

			}
		}
	}

	if (OCCUPIED_RAM + value <= MAX_RAM)
	{
		try
		{
			void* var = ::operator new(value);
			OCCUPIED_RAM += value;
			return var;
		}
		catch (std::exception e)
		{
			throw std::logic_error("cant allocate: no more memory");
		}
	}
	else
	{
		throw std::logic_error("cant allocate: no more memory");
	}
}





Expression::variable Expression::getVariable(std::string searchName)
{
	for (auto x : variables)
	{
		if (x.name == searchName)
		{
			return x;
		}
	}

	throw std::logic_error("Variable is not exist");
}

void Expression::addVariable(std::string name, void* ptr, size_t size)
{
	for (auto &x : variables)
	{
		if (x.name == name)
		{
			delete x.ptr;
			x.ptr = ptr;
			x.canDispose = false;
			x.size = size;
			return;
		}
	}

	variable var;
	var.ptr = ptr;
	var.name = name;
	var.canDispose = false;
	var.size = size;
	variables.push_back(var);
}



void Expression::printVariables()
{
	std::cout << "Variables: ";
	for (auto x : variables)
	{
		std::cout << x.name << ": " << x.canDispose <<"; ";
	}
	std::cout << "\n";
}

void Expression::_showvar()
{
	std::cout << "Variables: ";
	for (auto x : variables)
	{
		if (!x.canDispose)
		{
			std::cout << x.name <<"(" << x.size << "b); ";
		}
	}
	std::cout << "\n";
}

Expression::~Expression()
{
	for (auto x : variables)
	{
		delete x.ptr;
	}
}


