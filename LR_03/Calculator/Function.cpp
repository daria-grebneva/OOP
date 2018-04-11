#include "stdafx.h"

#include "Function.h"

using namespace std;

CFunction::CFunction() = default;
CFunction::~CFunction() = default;

functionValue CFunction::GetValue(std::string name)
{
	//TODO:: посмотреть чему равно и в альтернативном случае (если не найдено), вернуть сообщение, что не найдено
	return (*m_functions.find(name)).second;
}

void CFunction::SetValue(const std::string& identifier, functionValue result)
{
	(*m_functions.find(identifier)).second = result;
}

double CFunction::GetResult() const
{
	return m_result;
}

double CFunction::Calculate(double firstArgument, double secondArgument, char operation)
{
	return m_result;
}

bool CFunction::CreateNewFunction(std::string identificator1, std::string identificator2)
{
	//проверка на необъ€вленность идентификатора 1
	if (m_functions.find(identificator1) == m_functions.end())
	{
	}
}

bool CFunction::CreateNewFunction(std::string identificator1, std::string identificator2, char operation, std::string identificator3)
{
	//проверка на ранее объ€вленность идентификатор 2  и 3
	//если значение 2 или 3 не объ€вленно, то результат операции NAN
	//—лучай ошибки?? ƒеление на ноль или что?
}
