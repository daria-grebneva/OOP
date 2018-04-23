#pragma once
#include "Variable.h"

typedef std::map<std::string, double> variablesMap;

struct functionValue
{
	std::string operation = "";
	double value = 0;
};

typedef std::map<std::string, functionValue> functionMap;

class CFunction
{
public:
	CFunction(CVariable* myVariables);
	~CFunction();
	void CreateFunction(std::string, std::string);
	void CreateFunction(std::string, std::string, char, std::string);
	std::pair<std::string, functionValue> GetFunctionValue(std::string);
	functionMap GetFunctionValues();
	functionValue GetValueForFunctionMap(std::string);

private:
	CVariable* m_variablesPtr;
	functionMap m_functionMap;
	bool m_isFoundInMap = false;

	double MakeOperation(char, double, double);
	void UpdateValues(std::string);
	bool InitializeExpression(std::string, std::string&, std::string&, char&);
	bool CanGetFunction(std::string functionName);
	void UpdateValue(std::string valueName, functionValue& value, std::pair<std::string, functionValue> mapElement);
	bool InitializeOperation(std::string, char&);
};
