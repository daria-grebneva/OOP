#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

int FlipByte(int currentNumber)
{
	int result = 0;
	for (size_t i = 0; i < 8; i++)
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

bool IsDigit(string strInput)
{
	for (size_t i = 0; i < strInput.size(); i++)
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

	string inputByte = argv[1];

	if (IsDigit(inputByte))
	{
		int value = stoi(inputByte);

		if ((value < 0) || (value > 255))
		{
			cout << "Input value should be in range 0..255" << endl;
			return 1;
		}

		cout << int(FlipByte(value)) << endl;
	}
	else
	{
		cout << "Your input value is NOT a digit" << endl;
		return 1;
	}

	return 0;
}
