//Разработайте программу, выводящую числа Фибоначчи12 диапазона от 0 до N. 
//Целочисленный параметр N (верхняя граница) должен быть указан пользователем в виде аргумента командной строки. 
//Числа последовательности должны выводиться через запятую по 5 чисел в каждой строке.

#include "stdafx.h"
#include <string>
#include <errno.h>

int SumDigits(int pred, int next)
{
	return pred + next;
}

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	if (errno == ERANGE) {
		printf( "Incorrect value of the range: MORE THAN MAXINT");
		errno = 0;
		return 0;
	}
	if (param < 1) {
		printf("Incorrect value of the range: YOUR DIGIT IS LESS THAN 1");
		return 0;
	}

	return param;
}

int main(int argc, char* argv[])
{
	bool err;
	int param = StringToInt(argv[1], err);
	
	if (param == 0)
	{
		return 1;
	}

	if (err)
	{
		printf("Argument #%d is not a number\n.", 1);
		return 1;
	}

	int prev = 0;
	int curr = 1;
	int newDigit = prev + curr;
	printf("%d", prev);
	int counterForNewString = 1;

	while (newDigit <= param)
	{
		newDigit = prev + curr;
		prev = curr;
		curr = newDigit;
		printf(", ");
		if (counterForNewString % 5 == 0)
		{
			printf("\n", 1);
		}
		printf("%d", prev);
		counterForNewString++;
	}

    return 0;
}

