#pragma once
#include <iostream>
#include <string>

class CFunction
{
public:
	CFunction(std::string name);
	~CFunction();
	std::string GetName() const;

private:
	std::string m_functionName;
};
