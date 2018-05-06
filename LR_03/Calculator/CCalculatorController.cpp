#include "stdafx.h"
#include "CCalculatorController.h"

using namespace std;

CCalculatorController::CCalculatorController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CCalculatorController::ShowUsage()
{
	m_output << PRINT << " <= to print value of variable or function" << endl;
	m_output << PRINT_VARS << " <= to print all of variables" << endl;
	m_output << PRINT_FUNCTIONS << " <= to print all of functions" << endl;
	m_output << CREATE_FUNCTION << " <= to create function" << endl;
	m_output << CREATE_VARS << " <= to create a var" << endl;
	m_output << CHANGE_VAR << " <= to change the value of existing var or create new witn value" << endl;
	m_output << EXIT << " <= to exit" << endl;
	m_output << SHOW_USAGE << " <= to show usage" << endl;
}

bool CCalculatorController::ProcessCommand()
{
	std::string action;
	getline(m_input, action);

	if (action.find(CREATE_VARS) == 0)
	{
		CreateVar(action);
	}
	else if (action.find(CHANGE_VAR) == 0)
	{
		ChangeVar(action);
	}
	else if (action.find(PRINT_VARS) == 0)
	{
		PrintVars(action);
	}
	else if (action.find(PRINT_FUNCTIONS) == 0)
	{
		PrintFunctions(action);
	}
	else if (action.find(CREATE_FUNCTION) == 0)
	{
		CreateFunction(action);
	}
	else if (action.find(PRINT) == 0)
	{
		Print(action);
	}
	else if (action.find(SHOW_USAGE) == 0)
	{
		ShowUsage();
	}
	else if (action.find(EXIT) == 0)
	{
		return false;
	}
	else
	{
		m_output << "Command not found" << endl;
	}
	return true;
}

void CCalculatorController::Print(string& command)
{
	m_output << fixed;
	m_output.precision(2);
	string value = command.substr(PRINT.length() + 1, command.length());

	string identifierType = NONE;

	if (m_calculator.GetIdentifierValue(value, identifierType).first != NOT_FOUND)
	{
		m_output << m_calculator.GetIdentifierValue(value, identifierType).second << endl;
	}
	else
	{
		m_output << "Idenifier is not found" << endl;
	}
}

void CCalculatorController::PrintVars(const string& command) const
{
	m_output << fixed;
	m_output.precision(2);
	auto variables = m_calculator.GetAllVariable();
	for (auto& var : variables)
	{
		m_output << var.first << ' ' << var.second << endl;
	}
}

void CCalculatorController::PrintFunctions(const string& command)
{
	m_output << fixed;
	m_output.precision(2);
	auto functions = m_calculator.GetFunctionValues();
	string identifierType = NONE;
	for (auto& f : functions)
	{
		m_output << f.first << ' ' << m_calculator.GetIdentifierValue(f.first, identifierType).second << endl;
	}
}

void CCalculatorController::CreateFunction(const string& command)
{
	string identifier2 = command.substr(command.find("=") + 1, command.length());
	string identifier1 = command.substr(CREATE_FUNCTION.length() + 1, command.length() - 4 - identifier2.length());
	string value1, value2;

	char operation = CIdentifier::InitializeExpression(identifier2, value1, value2);
	int result;

	if (operation != ' ')
	{
		result = m_calculator.CreateNewFunction(identifier1, value1, operation, value2);
	}
	else
	{
		result = m_calculator.CreateNewFunction(identifier1, identifier2);
	}

	PrintResultOfOperation(result);
}

void CCalculatorController::CreateVar(const string& command)
{
	string nameOfValue = command.substr(CREATE_VARS.length() + 1, command.length());
	int result = m_calculator.CreateNewVariable(nameOfValue);

	PrintResultOfOperation(result);
}

void CCalculatorController::ChangeVar(const string& command)
{
	int result;
	string identifier2 = command.substr(command.find("=") + 1, command.length());
	string identifier1 = command.substr(CHANGE_VAR.length() + 1, command.length() - 5 - identifier2.length());

	if (IsNumber(identifier2))
	{
		double value = strtod(identifier2.c_str(), nullptr);
		result = m_calculator.ChangeValueOfIdentifier(identifier1, value);
	}
	else
	{
		result = m_calculator.ChangeValueOfIdentifier(identifier1, identifier2);
	}

	PrintResultOfOperation(result);
}

void CCalculatorController::PrintResultOfOperation(int result) const
{
	if (result == 1)
	{
		m_output << "The name of the identifier is invalid" << endl;
	}
	else if (result == 2)
	{
		m_output << "This identifier already exists" << endl;
	}
}

bool CCalculatorController::IsNumber(const string& number) const
{
	int pointCounter = 0;
	for (size_t k = 0; k < number.length(); k++)
		if (number[k] == '.')
			pointCounter++;

	if (pointCounter > 1)
	{
		return false;
	}
	for (auto& n : number)
	{
		if (!((n >= '0' && n <= '9') || n == '.'))
		{
			return false;
		}
	}

	return true;
}
