#include "stdafx.h"
#include "Function.h"

using namespace std;

CFunction::CFunction(CVariable* m_variables)
	: m_variablesPtr(m_variables)
{
}

CFunction::~CFunction() = default;

void CFunction::CreateFunction(string functionName, string addedFunctionName)
{
	functionValue value;
	value = GetValueForFunctionMap(addedFunctionName);
	m_functionMap.emplace(functionName, value);
}

void CFunction::CreateFunction(string functionName, string addedFunctionNameOne, char operation, string addedFunctionNameTwo)
{
	functionValue value1, value2, value3;

	value1 = GetValueForFunctionMap(addedFunctionNameOne);
	value2 = GetValueForFunctionMap(addedFunctionNameTwo);
	value3.operation = addedFunctionNameOne + operation + addedFunctionNameTwo;
	value3.value = MakeOperation(operation, value1.value, value2.value);
	m_functionMap.emplace(functionName, value3);
}

bool CFunction::CanGetFunction(string functionName)
{
	return (m_functionMap.find(functionName) != m_functionMap.end());
}

pair<string, functionValue> CFunction::GetFunctionValue(string NameOfFunction)
{

	pair<string, functionValue> pairForFunctionMap;
	pairForFunctionMap.first = VALUE_IS_NOT_EXIST;
	if (CanGetFunction(NameOfFunction))
	{
		if (m_variablesPtr->isNeedToUpdate() == false)
		{
			functionMap functionMapIn = GetFunctionValues();
			for (auto& x : m_functionMap)
			{
				UpdateValues(x.first);
			}

			m_variablesPtr->SetUpdate(true);
		}

		pairForFunctionMap = *m_functionMap.find(NameOfFunction);
	}
	return (pairForFunctionMap);
}

functionMap CFunction::GetFunctionValues()
{
	if (m_variablesPtr->isNeedToUpdate() == false)
	{
		for (auto& x : m_functionMap)
		{
			UpdateValues(x.first);
		}

		m_variablesPtr->SetUpdate(true);
	}
	return (m_functionMap);
}

functionValue CFunction::GetValueForFunctionMap(string functionName)
{
	functionValue value;

	if (m_variablesPtr->CanGetVariable(functionName))
	{
		value.operation = functionName;
		value.value = m_variablesPtr->GetVariable(functionName);
	}
	else
	{
		auto functionMapElement = GetFunctionValue(functionName);
		if (functionMapElement.first != VALUE_IS_NOT_EXIST)
		{
			value = functionMapElement.second;
		}
		else
		{
			value.operation = VALUE_IS_NOT_EXIST;
		}
	}
	return value;
}

void CFunction::UpdateValue(string valueName, functionValue& value, pair<string, functionValue> mapElement)
{
	if (CanGetFunction(valueName))
	{
		mapElement = *m_functionMap.find(valueName);
		value = mapElement.second;
	}
	else
	{
		value.value = m_variablesPtr->GetVariable(valueName);
	}
}

void CFunction::UpdateValues(string updateLine)
{
	functionValue value, value2;
	pair<string, functionValue> functionMapElementOne, functionMapElementTwo;
	functionMapElementOne = *m_functionMap.find(updateLine);
	value = functionMapElementOne.second;
	char operation;
	string firstValue;
	string secondValue;

	bool isOperation = InitializeExpression(value.operation, firstValue, secondValue, operation);

	if (!isOperation)
	{
		firstValue = value.operation;
	}

	if (CanGetFunction(firstValue))
	{
		UpdateValues(firstValue);
	}
	else
	{
		functionMapElementOne = *m_functionMap.find(updateLine);
		m_functionMap.erase(updateLine);
		value = functionMapElementOne.second;
		if (m_variablesPtr->CanGetVariable(value.operation))
		{
			value.value = m_variablesPtr->GetVariable(value.operation);
		}

		functionMapElementOne.second = value;
		m_functionMap.insert(functionMapElementOne);
	}

	if (isOperation)
	{
		if (CanGetFunction(secondValue))
		{
			UpdateValues(secondValue);
		}

		value = functionMapElementOne.second;
		m_functionMap.erase(updateLine);

		UpdateValue(firstValue, value2, functionMapElementTwo);

		double countValue1 = value2.value;

		UpdateValue(secondValue, value2, functionMapElementTwo);

		double countValue2 = value2.value;

		value.value = MakeOperation(operation, countValue1, countValue2);

		functionMapElementOne.second = value;
		m_functionMap.insert(functionMapElementOne);
	}
}

double CFunction::MakeOperation(char operation, double value1, double value2)
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

bool CFunction::InitializeOperation(std::string inputStr, char& operation)
{
	operation = ' ';
	if (inputStr.find('+') != -1)
		operation = '+';
	else if (inputStr.find('-') != -1)
		operation = '-';
	else if (inputStr.find('*') != -1)
		operation = '*';
	else if (inputStr.find('/') != -1)
		operation = '/';
	return (operation != ' ');
}

bool CFunction::InitializeExpression(string inputStr, string& firstValue, string& secondValue, char& operation)
{
	if (InitializeOperation(inputStr, operation))
	{
		firstValue = inputStr.substr(0, inputStr.find(operation));
		secondValue = inputStr.substr(inputStr.find(operation) + 1, inputStr.length());
		return true;
	}
	else
	{
		return false;
	}
}
