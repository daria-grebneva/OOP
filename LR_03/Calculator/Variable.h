#pragma once
#include <string>

class CVariable
{
public:
	CVariable(std::string name);
	~CVariable();
	std::string GetName() const;

private:
	std::string m_variableName;
};
