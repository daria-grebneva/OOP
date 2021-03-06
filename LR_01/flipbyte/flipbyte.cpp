#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

uint8_t FlipByte(uint8_t byte)
{
	uint8_t result = 0;
	for (unsigned int i = 0; i < 8; i++)
	{
		result = result << 1;
		result |= (byte & 1);
		byte = byte >> 1;
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

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong number of arguments. Please, enter your input: " << endl;
		cout << "<input byte>" << endl;
		return 1;
	}

	bool err;
	int value = StringToInt(argv[1], err);

	if (err)
	{
		cout << "Your input data is not a number" << endl;
		return 1;
	}

	uint8_t byteValue = static_cast<uint8_t>(value);

	if ((value < 0) || (value > 255))
	{
		cout << "Input value should be in range 0..255" << endl;
		return 1;
	}

	cout << static_cast<int> (FlipByte(byteValue)) << endl;

	return 0;
}
