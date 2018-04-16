#pragma once
#include <map>
#include <math.h>
#include <string>
typedef std::map<std::string, double> variablesMap;

class CVariable
{
public:
	CVariable();
	~CVariable();
	std::string GetName() const;
	void SetValue(const std::string& identifier, double result);
	double GetValue(std::string name);
	bool CreateVar(std::string identifier);
	variablesMap GetVariables() const;
	bool SetValueToVar(std::string identifierName, double result);

private:
	std::string m_variableName;
	double m_value = NAN;
	variablesMap m_variables;

	void CreateLet(std::string identifierName, double result);
};
