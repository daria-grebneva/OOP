#include "stdafx.h"
#include "ÑIdentifier.h"

using namespace std;

variable CIdentifier::GetAllVariable() const
{
	return m_variables;
}

function CIdentifier::GetFunctionValues() const
{
	return m_functions;
}

int CIdentifier::CreateNewVariable(string identifier)
{
	string identifierType = "none";
	if (IsIdentifier(identifier))
	{
		if (GetIdentifierValue(identifier, identifierType).first == NOT_FOUND)
		{
			m_variables.emplace(identifier, NAN);

			return 0;
		}

		return 2;
	}

	return 1;
}

pair<string, double> CIdentifier::GetIdentifierValue(string identifier, string& identifierType)
{
	pair<string, double> identifierValue = make_pair(NOT_FOUND, 0);

	if (m_variables.find(identifier) != m_variables.end())
	{
		identifierValue = *m_variables.find(identifier);
		identifierValue = make_pair("", identifierValue.second);
		identifierType = "variable";
	}
	else if (m_functions.find(identifier) != m_functions.end())
	{
		double value;
		CalculateFunctionValue(identifier, value);
		identifierValue = make_pair(identifier, value);
		identifierType = "function";
	}

	return identifierValue;
}

int CIdentifier::ChangeValueOfIdentifier(string identifier1, string identifier2)
{
	string identifierType1 = "none";
	if (GetIdentifierValue(identifier1, identifierType1).first != NOT_FOUND)
	{
		m_variables.erase(identifier1);
	}

	if (IsIdentifier(identifier1))
	{
		string identifierType2 = "none";
		if (GetIdentifierValue(identifier2, identifierType2).first != NOT_FOUND)
		{
			if (identifierType1 == "variable" || "none")
			{
				m_variables.emplace(identifier1, GetIdentifierValue(identifier2, identifierType2).second);
			}
			else
			{
				auto value = GetIdentifierValue(identifier2, identifierType2).second;
				m_functions.emplace(identifier1, to_string(value));
			}

			return 0;
		}

		return 1;
	}

	return 2;
}

int CIdentifier::ChangeValueOfIdentifier(string identifier, double value)
{
	string identifierType = "none";
	if (GetIdentifierValue(identifier, identifierType).first != NOT_FOUND)
	{
		m_variables.erase(identifier);
	}

	if (IsIdentifier(identifier))
	{
		m_variables.emplace(identifier, value);

		return 0;
	}

	return 1;
}

int CIdentifier::CreateNewFunction(string identifier1, string identifier2)
{
	if (IsIdentifier(identifier1))
	{
		string identifierType = "none";
		if (GetIdentifierValue(identifier2, identifierType).first != NOT_FOUND)
		{
			m_functions.insert(pair<string, string>(identifier1, identifier2));
			return 0;
		}

		return 2;
	}

	return 1;
}

int CIdentifier::CreateNewFunction(string identifier, string value1, char operation, string value2)
{
	if (IsIdentifier(identifier))
	{
		if (!IsFunctionExists(value1) || !IsFunctionExists(value2))
		{
			return 1;
		}

		m_functions.insert(pair<string, string>(identifier, value1 + operation + value2));

		return 0;
	}

	return 1;
}

bool CIdentifier::IsIdentifier(string identifier) const
{
	bool isIdentifier = true;

	if (identifier.empty())
	{
		isIdentifier = false;
	}

	if (identifier[0] >= '0' && identifier[0] <= '9')
	{
		isIdentifier = false;
	}

	for (auto& i : identifier)
	{
		if (i < '0' || (i > '9' && i < 'A' && i > 'Z' && i < '_' && i > '_' && i < 'a' && i > 'z'))
		{
			isIdentifier = false;
		}
	}

	return isIdentifier;
}

bool CIdentifier::IsFunctionExists(string function)
{
	string identifierType = "none";

	return (GetIdentifierValue(function, identifierType).first != NOT_FOUND);
}

double CIdentifier::MakeOperation(char operation, double value1, double value2)
{
	double result = NAN;
	if (!isnan(value1) && !isnan(value2))
	{
		switch (operation)
		{
		case '+':
			return (value1 + value2);
		case '-':
			return (value1 - value2);
		case '*':
			return (value1 * value2);
		case '/':
		{
			if (value2 != 0)
			{
				return (value1 / value2);
			}
		}
		}
	}

	return result;
}

char CIdentifier::InitializeExpression(string inputStr, string& value1, string& value2)
{
	char operation = InitializeOperation(inputStr);

	if (operation != ' ')
	{
		value1 = inputStr.substr(0, inputStr.find(operation));
		value2 = inputStr.substr(inputStr.find(operation) + 1, inputStr.length());
	}

	return operation;
}

char CIdentifier::InitializeOperation(std::string inputStr)
{
	char operation = ' ';

	if (inputStr.find('+') != -1)
	{
		operation = '+';
	}
	else if (inputStr.find('-') != -1)
	{
		operation = '-';
	}
	else if (inputStr.find('*') != -1)
	{
		operation = '*';
	}
	else if (inputStr.find('/') != -1)
	{
		operation = '/';
	}

	return operation;
}

void CIdentifier::CalculateFunctionValue(string function, double& value)
{
	string identifier1;
	string identifier2;
	string mainOperation;

	if (m_functions.find(function) != m_functions.end())
	{
		mainOperation = pair<string, string>(*m_functions.find(function)).second;
	}
	else
	{
		mainOperation = function;
	}

	char operation = InitializeExpression(mainOperation, identifier1, identifier2);

	if (operation != ' ')
	{
		double value1;
		double value2;
		CalculateFunctionValue(identifier1, value);
		value1 = value;
		CalculateFunctionValue(identifier2, value);
		value2 = value;
		value = MakeOperation(operation, value1, value2);
	}
	else
	{
		string identifierType = "none";
		value = GetIdentifierValue(mainOperation, identifierType).second;
	}
}
