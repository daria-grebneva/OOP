#pragma once
#include "stdafx.h"

const std::string NOT_FOUND = "Not found";
const std::string VAR = "variable";
const std::string FUNCTION = "function";

typedef std::map<std::string, double> variableMap;
typedef std::map<std::string, std::string> functionMap;

//TODO:: изменить тип данных у идентификаторов, возможно указатели на объекты
//struct FunctionValue
//{
//	string identifier1 = "";
//	string identifier2 = "";
//	char operation = ' ';
//	double value = NAN;
//};

class CIdentifier
{
public:
	CIdentifier() = default;
	~CIdentifier() = default;
	std::pair<std::string, double> GetIdentifierValue(std::string identifier, std::string& identifierType);
	variableMap GetAllVariable() const;
	functionMap GetFunctionValues() const;
	int CreateNewVariable(std::string identifier);
	int ChangeValueOfIdentifier(std::string identifier1, std::string identifier2);
	int ChangeValueOfIdentifier(std::string identifier, double value);
	int CreateNewFunction(std::string identifier1, std::string identifier2);
	int CreateNewFunction(std::string identifier, std::string value1, char operation, std::string value2);
	static char InitializeExpression(std::string inputStr, std::string& value1, std::string& value2);

private:
	static char InitializeOperation(std::string inputStr);
	bool IsIdentifier(std::string identifier) const;
	bool IsFunctionExists(std::string function);
	double MakeOperation(char operation, double value1, double value2);
	void CalculateFunctionValue(std::string function, double& value);

	variableMap m_variables;
	functionMap m_functions;
};
