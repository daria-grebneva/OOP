//Разработайте программу, выводящую в порядке возрастания все целые числа диапазона от 1 до 1000, делящиеся без остатка на сумму своих цифр.

#include "stdafx.h"
#include <errno.h>
#include <string>

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

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	if (errno == ERANGE) {
		printf("Incorrect value of the range: MORE THAN MAXINT");
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

	for (int i = 1; i <= param; ++i)
	{
		if ((i != 1) && (((i - 1) % SumDigits(i - 1)) == 0))
		{
			printf(", ");
		}

		int sum = SumDigits(i);

		if ((i % sum) == 0)
		{
			printf("%d", i);
		}
	}

	return 0;
}

