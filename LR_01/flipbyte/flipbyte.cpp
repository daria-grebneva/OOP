#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

uint8_t FlipByte(uint8_t currentNumber)
{
	uint8_t result = 0;
	for (unsigned int i = 0; i < 8; i++)
	{
		result = result << 1; //побитовый сдвиг влево
		if ((currentNumber & 1) == 1) //побитовое И
		{
			result |= 1; //побитовое ИЛИ
		}
		currentNumber = currentNumber >> 1; //побитовый сдвиг вправо
	}
	return result;
}

int StringToInt(const char* str, bool& err)
{
	char* pLastChar = NULL;
	int intFromStr = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));

	return intFromStr;
}

bool IsDigit(const string& strInput)
{
	for (unsigned int i = 0; i < strInput.size(); i++)
	{
		if (!isdigit(strInput[i]))
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Please, enter arguments" << endl;
		return 1;
	}
	else if (argc > 2)
	{
		cout << "Too much arguments" << endl;
		return 1;
	}

	bool err;
	int value = StringToInt(argv[1], err);

	if (err)
	{
		cout << "Your input data is not a number" << endl;
		return 1;
	}

	if (IsDigit(argv[1]))
	{

		uint8_t byteValue = static_cast<uint8_t>(value);

		if ((value < 0) || (value > 255))
		{
			cout << "Input value should be in range 0..255" << endl;
			return 1;
		}

		cout << int(FlipByte(byteValue)) << endl;
	}
	else
	{
		cout << "Your input value is NOT a digit" << endl;
		return 1;
	}

	return 0;
}
