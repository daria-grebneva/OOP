#include "stdafx.h"
#include "CalculatorController.h"

using namespace std;

CCalculatorController::CCalculatorController(CVariable* variable, CFunction* function)
	: m_variables(variable)
	, m_functions(function)
{
}

CCalculatorController::~CCalculatorController() = default;

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

void CCalculatorController::ProcessCommand(string command)
{
	if (command.find(CREATE_VARS) == 0)
		CreateVar(command);
	else if (command.find(CHANGE_VAR) == 0)
		ChangeVar(command);
	else if (command.find(PRINT_VARS) == 0)
		PrintVars(command);
	else if (command.find(PRINT_FUNCTIONS) == 0)
		PrintFunctions(command);
	else if (command.find(CREATE_FUNCTION) == 0)
		CreateFunction(command);
	else if (command.find(PRINT) == 0)
		Print(command);
	else
		cout << "Command does not exist" << endl;
}

void CCalculatorController::Print(string command) const
{
	try
	{
		cout << fixed;
		cout.precision(2);

		string valueName = command.substr(PRINT.length() + 1, command.length());

		auto functionValueId = m_functions->GetFunctionValue(valueName);

		if (m_variables->CanGetVariable(valueName))
		{
			cout << m_variables->GetVariable(valueName) << endl;
		}
		else if (functionValueId.first != VALUE_IS_NOT_EXIST)
		{
			auto valueInFunction = functionValueId.second;
			cout << valueInFunction.value << endl;
		}
		else
		{
			cout << "Identifier " << valueName << " not found" << endl;
		}
	}
	catch (std::exception& e)
	{
		cerr << e.what() << endl;
	}
}

void CCalculatorController::PrintVars(string command) const
{
	cout << fixed;
	cout.precision(2);

	if (command.length() == PRINT_VARS.length())
	{
		auto variablesForPrint = m_variables->GetVariables();
		if (variablesForPrint.size() != 0)
		{
			for (auto& x : variablesForPrint)
			{
				cout << x.first << ' ' << x.second << endl;
			}
		}
	}
}

void CCalculatorController::PrintFunctions(string command) const
{

	cout << fixed;
	cout.precision(2);

	if (command.length() == PRINT_FUNCTIONS.length())
	{
		auto printedFunction = m_functions->GetFunctionValues();
		if (printedFunction.size() != 0)
			for (auto& x : printedFunction)
			{
				auto functionVal = x.second;
				cout << x.first << ' ' << functionVal.value << endl;
			}
	}
}

void CCalculatorController::CreateVar(string command)
{
	string valueName = command.substr(CREATE_VARS.length() + 1, command.length());

	auto functionValue = m_functions->GetFunctionValue(valueName);
	if (functionValue.first != VALUE_IS_NOT_EXIST)
		cout << "Duplicate identifier name" << endl;
	else
	{
		auto operationResult = m_variables->CreateVariable(valueName);
		if (!IsCorrectIdentifier(valueName))
		{
			cout << "Wrong variable name" << endl;
		}
		else
		{
			if (operationResult)
				cout << "Variable \"" << valueName << "\" was successfully created" << endl;
			else if (!operationResult)
				cout << "An identifier with this name was previously created" << endl;
		}
	}
}

bool CCalculatorController::IsValidVarData(string valueName)
{
	bool isValid = true;
	if (!IsCorrectIdentifier(valueName))
	{
		isValid = false;
		cout << "Wrong variable name" << endl;
	}
	return isValid;
}

void CCalculatorController::ChangeVar(string command)
{
	string valueNameTwo = command.substr(command.find("=") + 1, command.length());
	string valueNameOne = command.substr(CHANGE_VAR.length() + 1, command.length() - 5 - valueNameTwo.length());

	auto functionValueId = m_functions->GetFunctionValue(valueNameOne);

	if (functionValueId.first != VALUE_IS_NOT_EXIST)
		cout << "Duplicate identifier name" << endl;
	else
	{
		double value = strtod(valueNameTwo.c_str(), nullptr);
		if (IsNumber(valueNameTwo))
		{

			if (IsValidVarData(valueNameOne))
			{
				m_variables->ChangeVariableValue(valueNameOne, value);
				cout << "Variable \"" << valueNameOne << "\" was successfully created with values " << value << endl;
			}
		}
		else
		{
			functionValueId = m_functions->GetFunctionValue(valueNameTwo);
			if (functionValueId.first != VALUE_IS_NOT_EXIST)
			{
				auto valueInFunction = functionValueId.second;
				value = valueInFunction.value;

				if (IsValidVarData(valueNameOne))
				{
					m_variables->ChangeVariableValue(valueNameOne, value);
					cout << "Variable \"" << valueNameOne << "\" was successfully created with values from identifier " << valueNameTwo << endl;
				}
			}
			else
			{
				if (IsValidVarData(valueNameOne) && IsValidVarData(valueNameTwo))
				{
					if (IsVariableExist(m_variables, valueNameOne))
					{
						m_variables->ChangeVariableValue(valueNameOne, valueNameTwo);
						cout << "Variable \"" << valueNameOne << "\" was successfully created with values from identifier " << valueNameTwo << endl;
					}
					else
					{
						cout << "Variable \"" << valueNameTwo << "\" does not exist.";
					}
				}
			}
		}
	}
}

bool CCalculatorController::IsVariableExist(const CVariable* m_variables, string valueName)
{
	auto vars = m_variables->GetVariables();
	return (vars.find(valueName) != vars.end());
}

bool CCalculatorController::IsNumber(string number)
{
	int pointCounter = 0;
	for (size_t k = 0; k < number.length(); k++)
	{
		if (number[k] == '.')
		{
			pointCounter++;
		}
	}

	if (pointCounter > 1)
	{
		return false;
	}

	for (size_t k = 0; k < number.length(); k++)
	{
		if (!((number[k] >= '0' && number[k] <= '9') || number[k] == '.'))
		{
			return false;
		}
	}

	return true;
}

bool CCalculatorController::IsValidFunctionIdData(string valueName, string valueOne, string valueTwo)
{
	bool isRight = false;
	if (!IsCorrectIdentifier(valueName))
	{
		cout << "Wrong identifier name" << endl;
	}
	else if (IsVariableExist(m_variables, valueName))
	{
		cout << "Duplicate identifier name" << endl;
	}
	else if (IsValueInFunctionMap(valueOne) || IsValueInFunctionMap(valueTwo))
	{
		cout << "Function was not declared" << endl;
	}
	else
	{
		cout << "Function named \"" << valueName << "\" was successfully created" << endl;
		isRight = true;
	}
	return isRight;
}

bool CCalculatorController::IsValidFunctionData(string valueName, string value)
{
	bool isRight = false;
	if (!IsCorrectIdentifier(valueName))
	{
		cout << "Wrong identifier name" << endl;
	}
	else if (IsVariableExist(m_variables, valueName))
	{
		cout << "Duplicate identifier name" << endl;
	}
	else if (IsValueInFunctionMap(value))
	{
		cout << "Function was not declared" << endl;
	}
	else
	{
		cout << "Function named \"" << valueName << "\" was successfully created" << endl;
		isRight = true;
	}
	return isRight;
}

void CCalculatorController::CreateFunction(string command)
{
	string valueNameTwo = command.substr(command.find("=") + 1, command.length());
	string valueNameOne = command.substr(CREATE_FUNCTION.length() + 1, command.length() - 4 - valueNameTwo.length());
	string calculatedValueOne;
	string calculatedValueTwo;
	char operation;
	bool isOperation = InitializeExpression(valueNameTwo, calculatedValueOne, calculatedValueTwo, operation);
	if (isOperation)
	{
		if (IsValidFunctionIdData(valueNameOne, calculatedValueOne, calculatedValueTwo))
		{
			m_functions->CreateFunction(valueNameOne, calculatedValueOne, operation, calculatedValueTwo);
		}
	}
	else
	{
		if (IsValidFunctionData(valueNameOne, valueNameTwo))
		{
			m_functions->CreateFunction(valueNameOne, valueNameTwo);
		}
	}
}

bool CCalculatorController::InitializeExpression(string inputStr, string& firstValueName, string& secondValueName, char& operation)
{
	operation = ' ';
	auto p = inputStr.find('+');
	if (inputStr.find('+') != -1)
		operation = '+';
	else if (inputStr.find('-') != -1)
		operation = '-';
	else if (inputStr.find('*') != -1)
		operation = '*';
	else if (inputStr.find('/') != -1)
		operation = '/';

	if (operation != ' ')
	{
		firstValueName = inputStr.substr(0, inputStr.find(operation));
		secondValueName = inputStr.substr(inputStr.find(operation) + 1, inputStr.length());
		return (true);
	}
	else
		return (false);
}

bool CCalculatorController::IsCorrectIdentifier(string str)
{
	bool isCorrect = true;
	if (str.empty() || (str[0] >= '0' && str[0] <= '9'))
	{
		isCorrect = false;
	}

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] < '0' || (str[i] > '9' && str[i] < 'A' && str[i] > 'Z' && str[i] < '_' && str[i] > '_' && str[i] < 'a' && str[i] > 'z'))
		{
			isCorrect = false;
		}
	}

	return isCorrect;
}

bool CCalculatorController::IsValueInFunctionMap(const string& addedFunctionName)
{
	functionValue value;
	value = m_functions->GetValueForFunctionMap(addedFunctionName);
	return (value.operation == VALUE_IS_NOT_EXIST);
}
