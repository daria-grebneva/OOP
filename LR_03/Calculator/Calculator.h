#pragma once
#include "Function.h"
#include "Variable.h"
#include <iomanip>
#include <iostream>
#include <string>

class CCalculator
{
public:
	CCalculator();
	~CCalculator();
	std::string Var(const std::string& identifier);
	void Let(const std::string& identifier, double result);
	void Let(const std::string& identifierOne, const std::string& identifierTwo);

private:
	CFunction m_function;
	CVariable m_variable;
};
