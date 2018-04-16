#include "stdafx.h"

#include "Calculator.h"

using namespace std;
CCalculator::CCalculator()
	: m_function()
	, m_variable()
{
}

CCalculator::~CCalculator() = default;

string CCalculator::Var(const std::string& identifier)
{
	if (!m_variable.CreateVar(identifier))
	{
		return "This variable is already exist";
	}
	else
		return "";
}

void CCalculator::Let(const std::string& identifier, double result)
{
	CVariable var;
	if (!var.SetValueToVar(identifier, result))
	{
		Var(identifier);
	}

	var.SetValue(identifier, result);
}

void CCalculator::Let(const std::string& identifierOne, const std::string& identifierTwo)
{
	CVariable var;
	double result = var.GetValue(identifierTwo);
	Let(identifierOne, result);
}

void PrintVars()
{
	CVariable var;
	variablesMap allVariables = var.GetVariables();
	for (auto& item : allVariables)
	{
		cout << item.first << " : " << std::fixed << std::setprecision(2) << item.second << endl;
	}
}

void PrintFns()
{
	CVariable var;
	variablesMap allVariables = var.GetVariables();
	for (auto& item : allVariables)
	{
		cout << item.first << " : " << std::fixed << std::setprecision(2) << item.second << endl;
	}
}
