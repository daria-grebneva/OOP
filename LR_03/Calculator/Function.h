#pragma once

#include "Variable.h"
#include <iostream>
#include <map>
#include <string>

typedef map<std::string, double> valiousMap;
struct functionValue
{
	std::string operation;
	double result = 0;
};

typedef map<string, functionValue> functionMap;

class CFunction
{
public:
	CFunction();
	~CFunction();
	std::string GetName() const;
	double GetResult() const;
	double Calculate(double firstArgument, double secondArgument, char operation);

	functionValue GetValue(std::string name);
	bool CreateNewFunction(std::string identificator1, std::string identificator2);
	bool CreateNewFunction(std::string identificator1, std::string identificator2, char operation, std::string identificator3);

	void SetValue(const std::string& identifier, functionValue result);

private:
	valiousMap m_values;
	functionMap m_functions;
	std::string m_functionName;
	double m_result = NAN;
};
//TODO:: 1) enum class of operations.
//2) char to enum + enum to char functions
enum Operation : char
{

};
