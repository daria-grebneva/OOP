#include "stdafx.h"

#include "Function.h"

using namespace std;

CFunction::CFunction() = default;
CFunction::~CFunction() = default;

functionValue CFunction::GetValue(std::string name)
{
	//TODO:: ���������� ���� ����� � � �������������� ������ (���� �� �������), ������� ���������, ��� �� �������
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
	//�������� �� ��������������� �������������� 1
	if (m_functions.find(identificator1) == m_functions.end())
	{
	}
}

bool CFunction::CreateNewFunction(std::string identificator1, std::string identificator2, char operation, std::string identificator3)
{
	//�������� �� ����� ������������� ������������� 2  � 3
	//���� �������� 2 ��� 3 �� ����������, �� ��������� �������� NAN
	//������ ������?? ������� �� ���� ��� ���?
}
