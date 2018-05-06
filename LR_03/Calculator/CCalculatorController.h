#pragma once

#include "ÑIdentifier.h"

const std::string PRINT = "print";
const std::string PRINT_VARS = "printvars";
const std::string PRINT_FUNCTIONS = "printfns";
const std::string CREATE_FUNCTION = "fn";
const std::string CREATE_VARS = "var";
const std::string CHANGE_VAR = "let";

class CCalculatorController
{
public:
	CCalculatorController() = default;
	void ProcessCommand(std::string& command);
	void ShowUsage();
	~CCalculatorController() = default;

private:
	void Print(const std::string& command);
	void PrintVars(const std::string& command) const;
	void PrintFunctions(const std::string& command);
	void CreateFunction(const std::string& command);
	void CreateVar(const std::string& command);
	void ChangeVar(const std::string& command);
	bool InitializeExpression(std::string inputStr, std::string& valueName1, std::string& valueName2, char& operation);
	void PrintResultOfOperation(int result) const;
	bool IsNumber(const std::string& number) const;
	CIdentifier m_calculator;
};
