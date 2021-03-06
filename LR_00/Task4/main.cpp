﻿// Задание: На основе данной программы разработайте программу eval.exe, вычисляющую результат вычисления арифметического выражения, 
//операции и операнды которого передаются через аргументы командной строки. 
//Вычисление выражения должно осуществляться без учета приоритета операторов, результат выводится с точностью до 3 знаков после запятой. 
#include "stdafx.h"

#include "stdlib.h"
#include <cerrno>
#include <iostream>
#include <iomanip>

using namespace std;

double StringToDouble(const char * str, bool & err)
{
	char * pLastChar = NULL;
	double doubleFromStr = strtod(str, &pLastChar);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	if (errno == ERANGE) {
		cout << "Incorrect value of the range: MORE THAN MAXINT" << endl;
		errno = 0;
		return 0;
	}

	return doubleFromStr;
}

double Calculate(char sign, double a, double b)
{
	if (sign == '+')
	{
		return a + b;
	}
	else if (sign == '-')
	{
		return a - b;
	}
	else if (sign == '/')
	{
		return a / b;
	}
	else if (sign == '*')
	{
		return a * b;
	}
}

bool CheckEmptyString(const char * str, bool & err)
{
	if ((err) && (*str != '+') && (*str != '-') && (*str != '/') && (*str != '*'))
	{
		cout << "One of arguments is not a number" << endl;
		return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "Program calculates sum of its command line arguments" << endl;

		return 0;
	}

	int sum = 0;

	double value1 = 0;
	double value2 = 0;
	char sign = ' ';
	for (int i = 1; i < argc; ++i)
	{
		bool err;

		if (i == 1)
		{
			value1 = StringToDouble(argv[i], err);
			if (CheckEmptyString(argv[i], err))
			{
				return 1;
			}

		}
		else if ((*argv[i] != '+') && (*argv[i] != '-') && (*argv[i] != '/') && (*argv[i] != '*'))
		{
			value2 = StringToDouble(argv[i], err);
			if (CheckEmptyString(argv[i], err))
			{
				return 1;
			}
			if ((value2 == 0) && (sign == '/'))
			{
				cout << "You can't divide by zero" << endl;
				return 1;
			}
			else
			{
				value1 = Calculate(sign, value1, value2);
			}
		}
		if (*argv[i] == '+')
		{
			sign = '+';
		}
		else if (*argv[i] == '-')
		{
			sign = '-';
		}
		else if (*argv[i] == '/')
		{
			sign = '/';
		}
		else if (*argv[i] == '*')
		{
			sign = '*';
		}
	}
	cout << "Result = " << fixed << setprecision(3) << value1 << endl;

	return 0;
}