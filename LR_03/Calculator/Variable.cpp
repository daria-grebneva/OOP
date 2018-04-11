#include "stdafx.h"

#include "Variable.h"

using namespace std;

CVariable::CVariable() = default;

string CVariable::GetName() const
{
	return m_variableName;
}

void CVariable::SetValue(const std::string& identifier, double result)
{
	(*m_variables.find(identifier)).second = result;
}

double CVariable::GetValue(string name)
{
	//TODO:: посмотреть чему равно и в альтернативном случае (если не найдено), вернуть сообщение, что не найдено
	return (*m_variables.find(name)).second;
}

bool CVariable::CreateVar(string identifier)
{
	if (m_variables.find(identifier) == m_variables.end())
	{
		m_variables.insert(pair<string, double>(identifier, NAN));
		return true;
	}
	return false;
}

variablesMap CVariable::GetVariables() const
{
	return (m_variables);
};

void CVariable::CreateLet(string identifierName, double result)
{
	CreateVar(identifierName);
	SetValueToVar(identifierName, result);
}

bool CVariable::SetValueToVar(string identifierName, double result)
{
	if (m_variables.find(identifierName) != m_variables.end())
	{
		m_variables.erase(identifierName);
		m_variables.insert(pair<string, double>(identifierName, result));
		return true;
	}
	else
	{
		CreateLet(identifierName, result);
		return false;
	}
};

CVariable::~CVariable() = default;
