#include "stdafx.h"
#include "Variable.h"

using namespace std;

CVariable::CVariable() = default;

CVariable::~CVariable() = default;

bool CVariable::CanGetVariable(std::string variableName)
{
	return (m_variables.find(variableName) != m_variables.end());
}

double CVariable::GetVariable(string variableName) const
{
	auto var = *m_variables.find(variableName);
	return (var.second);
}

int CVariable::CreateVariable(string identifier)
{
	if (!CanGetVariable(identifier))
	{
		m_variables.emplace(identifier, NAN);
		return (0);
	}
	else
		return (1);
}

variablesMap CVariable::GetVariables() const
{
	return (m_variables);
};

bool CVariable::isNeedToUpdate()
{
	return m_isUpdated;
}

void CVariable::SetUpdate(bool value)
{
	m_isUpdated = value;
}

void CVariable::ChangeVariableValue(string fisrtVariableName, string secondVariableName)
{
	m_isUpdated = false;

	//!!
	isUpdated = false;
	if (fisrtVariableName != secondVariableName)
	{
		pair<string, double> identifier;
		identifier = *m_variables.find(secondVariableName);
		if (CanGetVariable(fisrtVariableName))
		{
			m_variables.erase(fisrtVariableName);
		}
		m_variables.emplace(fisrtVariableName, identifier.second);
	}
};

void CVariable::ChangeVariableValue(string variableName, double value)
{
	m_isUpdated = false;

	//!!
	isUpdated = false;
	if (CanGetVariable(variableName))
	{
		m_variables.erase(variableName);
	}
	m_variables.emplace(variableName, value);
}
