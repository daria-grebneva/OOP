//Разработайте программу, выводящую в порядке возрастания все целые числа диапазона от 1 до 1000, делящиеся без остатка на сумму своих цифр.

#include "stdafx.h"

#include <errno.h>
#include <string>
#include <iostream>

using namespace std;

int SumDigits(int i)
{
	int sum = 0;
	// цикл продолжается до тех пор, пока число не станет равным 0
	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
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

	if (* argv[1] == '0')
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
	
	for (int i = 1; i <= upperBound; ++i)
	{
		int sum = SumDigits(i);

		if ((i % sum) == 0)
		{
			if (i != 1) cout << ", ";
			cout << i;
		}
	}
	cout << endl;

	return 0;
}
