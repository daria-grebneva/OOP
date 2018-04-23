#pragma once
#include "Function.h"
#include "Variable.h"

class CCalculatorController
{
public:
	CCalculatorController(CVariable* variable, CFunction* function);
	~CCalculatorController();
	void ProcessCommand(std::string command);
	void ShowUsage();

private:
	void Print(std::string command) const;
	void PrintVars(std::string command) const;
	void PrintFunctions(std::string command) const;
	void CreateFunction(std::string command);
	void CreateVar(std::string command);
	void ChangeVar(std::string command);
	bool InitializeExpression(std::string inputLine, std::string& valueName1, std::string& valueName2, char& operation);
	bool IsNumber(std::string number);
	bool IsCorrectIdentifier(std::string str);
	bool IsVariableExist(const CVariable* m_variables, std::string valueName);
	bool IsValueInFunctionMap(const std::string& addedFunctionName);
	bool IsValidFunctionIdData(std::string valueName, std::string valueOne, std::string valueTwo);
	bool IsValidFunctionData(std::string valueName, std::string value);
	bool IsValidVarData(std::string valueName);

	CVariable* m_variables;
	CFunction* m_functions;
};
