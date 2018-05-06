#include "stdafx.h"
#include "CCalculatorController.h"

using namespace std;

void CCalculatorController::ShowUsage()
{
	cout << PRINT << " <= to print value of variable or function" << endl;
	cout << PRINT_VARS << " <= to print all of variables" << endl;
	cout << PRINT_FUNCTIONS << " <= to print all of functions" << endl;
	cout << CREATE_FUNCTION << " <= to create function" << endl;
	cout << CREATE_VARS << " <= to create a var" << endl;
	cout << CHANGE_VAR << " <= to change the value of existing var or create new witn value" << endl;
	cout << EXIT << " <= to exit" << endl;
	cout << SHOW_USAGE << " <= to show usage" << endl;
}

void CCalculatorController::ProcessCommand(string& command)
{
	if (command.find(CREATE_VARS) == 0)
	{
		CreateVar(command);
	}
	else if (command.find(CHANGE_VAR) == 0)
	{
		ChangeVar(command);
	}
	else if (command.find(PRINT_VARS) == 0)
	{
		PrintVars(command);
	}
	else if (command.find(PRINT_FUNCTIONS) == 0)
	{
		PrintFunctions(command);
	}
	else if (command.find(CREATE_FUNCTION) == 0)
	{
		CreateFunction(command);
	}
	else if (command.find(PRINT) == 0)
	{
		Print(command);
	}
	else
	{
		cout << "Command not found" << endl;
	}
}

void CCalculatorController::Print(const string& command)
{
	cout << fixed;
	cout.precision(2);
	string value = command.substr(PRINT.length() + 1, command.length());

	string identifierType = NONE;

	if (m_calculator.GetIdentifierValue(value, identifierType).first != NOT_FOUND)
	{
		cout << m_calculator.GetIdentifierValue(value, identifierType).second << endl;
	}
	else
	{
		cout << "Idenifier is not found" << endl;
	}
}

void CCalculatorController::PrintVars(const string& command) const
{
	auto variables = m_calculator.GetAllVariable();
	for (auto& var : variables)
	{
		cout << var.first << ' ' << var.second << endl;
	}
}

void CCalculatorController::PrintFunctions(const string& command)
{
	auto functions = m_calculator.GetFunctionValues();
	string identifierType = NONE;
	for (auto& f : functions)
	{
		cout << f.first << ' ' << m_calculator.GetIdentifierValue(f.first, identifierType).second << endl;
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
		cout << "The name of the identifier is invalid" << endl;
	}
	else if (result == 2)
	{
		cout << "This identifier already exists" << endl;
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
