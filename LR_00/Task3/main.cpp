//Разработайте программу, выводящую числа Фибоначчи12 диапазона от 0 до N. 
//Целочисленный параметр N (верхняя граница) должен быть указан пользователем в виде аргумента командной строки. 
//Числа последовательности должны выводиться через запятую по 5 чисел в каждой строке.

#include "stdafx.h"

#include <string>
#include <errno.h>
#include <iostream>

using namespace std;

const int MAXINT = 2147483647;

int SumDigits(int pred, int next)
{
	return pred + next;
}

int StringToInt(const char* str, bool& err)
{
	char* pLastChar = NULL;
	int intFromStr = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	if (errno == ERANGE)
	{
		cout << "Incorrect value of the range: MORE THAN MAXINT" << endl;
		errno = 0;
		return 0;
	}

	return intFromStr;
}

int main(int argc, char* argv[])
{
	bool err;

	if (argc == 1)
	{
		cout << "Please, enter argument" << endl;
		return 1;
	}

	if (*argv[1] == '0')
	{
		cout << "Incorrect value of the range: YOUR DIGIT IS LESS THAN 1" << endl;
		return 1;
	}

	int upperBound = StringToInt(argv[1], err);

	if (upperBound == 0)
	{
		return 1;
	}

	if (upperBound < 1)
	{
		cout << "Incorrect value of the range: YOUR DIGIT IS LESS THAN 1" << endl;
		return 1;
	}

	if (err)
	{
		cout << "One of arguments is not a number" << endl;
		return 1;
	}

	int prev = 0;
	int curr = 1;
	int newSequenceElem = prev + curr;
	cout << prev;
	int rowCounter = 1;

	while (newSequenceElem <= upperBound)
	{
		if (prev > MAXINT - curr)
		{
			cout << endl;
			return 1;
		}
		newSequenceElem = prev + curr;
		prev = curr;
		curr = newSequenceElem;
		cout << ", ";
		if (rowCounter % 5 == 0)
		{
			cout << endl;
		}
		cout << prev;
		rowCounter++;
	}
	cout << endl;

    return 0;
}

