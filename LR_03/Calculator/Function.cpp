#include "stdafx.h"

#include "Function.h"

using namespace std;

CFunction::CFunction() = default;
CFunction::~CFunction() = default;

functionValue CFunction::GetValue(std::string name)
{
	//TODO:: ���������� ���� ����� � � �������������� ������ (���� �� �������), ������� ���������, ��� �� �������
	return (*m_functions.find(name)).second;
}

void CFunction::SetValue(const std::string& identifier, functionValue result)
{
	(*m_functions.find(identifier)).second = result;
}

double CFunction::GetResult() const
{
	return m_result;
}

double CFunction::Calculate(double firstArgument, double secondArgument, char operation)
{
	return m_result;
}

functionValue CFunction::GetValueForFunctionMap(string nameOfAddedFunction)
{
	pair<string, functionValue> pairForFunctionMap;
	functionValue value;
	if (m_functions.find(nameOfAddedFunction) == m_functions.end())
	{
		value.operation = nameOfAddedFunction;
		value.value = GetVariableInFunction(nameOfAddedFunction);
		return (value);
	}
	else
	{
		pair<string, functionValue> pairForFunctionMap;
		pairForFunctionMap = GetFunctionValue(nameOfAddedFunction);
		if (pairForFunctionMap.first != NOT_FOUND_IN_FUNCTION_MAP)
		{
			value = pairForFunctionMap.second;
			return (value);
		}
		else
		{
			value.operation = NOT_FOUND_IN_FUNCTION_MAP;
			return value;
		}
	}
}

bool CFunction::CreateNewFunction(std::string identificator1, std::string identificator2)
{
	//�������� �� ��������������� �������������� 1
	if (m_functions.find(identificator1) == m_functions.end())
	{
		m_functions.emplace(identificator1, identificator2);
		return true;
	}
	return false;
}

bool CFunction::CreateNewFunction(std::string identificator1, std::string identificator2, char operation, std::string identificator3)
{
	//�������� �� ����� ������������� ������������� 2  � 3
	//���� �������� 2 ��� 3 �� ����������, �� ��������� �������� NAN
	//������ ������?? ������� �� ���� ��� ���?
}
