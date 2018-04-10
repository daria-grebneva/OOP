#include "stdafx.h"

#include "Function.h"

using namespace std;

CFunction::CFunction(string name)
	: m_functionName(name)
{
}

string CFunction::GetName() const
{
	return m_functionName;
}

CFunction::~CFunction() = default;
