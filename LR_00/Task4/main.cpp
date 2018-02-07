// Задание: На основе данной программы разработайте программу eval.exe, вычисляющую результат вычисления арифметического выражения, 
//операции и операнды которого передаются через аргументы командной строки. 
//Вычисление выражения должно осуществляться без учета приоритета операторов, результат выводится с точностью до 3 знаков после запятой. 
#include "stdafx.h"
#include "stdlib.h"
#include <cerrno>

double StringToDouble(const char * str, bool & err)
{
	char * pLastChar = NULL;
	double param = strtod(str, &pLastChar);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	if (errno == ERANGE) {
		printf("Incorrect value of the range: MORE THAN MAXINT");
		errno = 0;
		return 0;
	}

	return param;
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
		printf("Argument #%d is not a number\n.", 1);
		return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("Program calculates sum of its command line arguments.\n");

		return 0;
	}

	int sum = 0;

	double param1 = 0;
	double param2 = 0;
	char sign = ' ';
	for (int i = 1; i < argc; ++i)
	{
		bool err;

		if (i == 1)
		{
			param1 = StringToDouble(argv[i], err);
			if (CheckEmptyString(argv[i], err))
			{
				return 1;
			}

		}
		else if ((*argv[i] != '+') && (*argv[i] != '-') && (*argv[i] != '/') && (*argv[i] != '*'))
		{
			param2 = StringToDouble(argv[i], err);
			if (CheckEmptyString(argv[i], err))
			{
				return 1;
			}
			if ((param2 == 0) && (sign == '/'))
			{
				printf("You can't divide by zero\n");
				return 1;
			}
			else
			{
				param1 = Calculate(sign, param1, param2);
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

	printf("Result = %.3f", param1);

	return 0;
}