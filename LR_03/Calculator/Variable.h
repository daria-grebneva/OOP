#pragma once

typedef std::map<std::string, double> variablesMap;

class CVariable
{
public:
	CVariable();
	~CVariable();
	bool CanGetVariable(const std::string& variableName);
	double GetVariable(const std::string& variableName) const;
	variablesMap GetVariables() const;
	bool CreateVariable(const std::string& identifier);
	void ChangeVariableValue(std::string fisrtVariableName, std::string secondVariableName);
	void ChangeVariableValue(std::string variableName, double value);
	double isUpdated = false;
	bool isNeedToUpdate();

	void SetUpdate(bool value);

private:
	bool m_isUpdated = false;
	variablesMap m_variables;
};
