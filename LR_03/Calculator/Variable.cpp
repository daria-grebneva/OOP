#include "stdafx.h"

#include "Variable.h"

using namespace std;

CVariable::CVariable(string name)
	: m_variableName(name)
{
}

string CVariable::GetName() const
{
	return m_variableName;
}

CVariable::~CVariable() = default;
