﻿#include "stdafx.h"

#include <cerrno>
#include <cmath>
#include <iostream>

using namespace std;

const int SIZE_OF_DATA = 200;
const double PI = 3.141592653;
const double ACCELERATION_OF_GRAVITY = 9.8;

double StringToDouble(const char* str, bool& err)
{
	char* pLastChar = NULL;
	double doubleFromStr = strtod(str, &pLastChar);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	if (errno == ERANGE)
	{
		cout << "Incorrect value of the range: MORE THAN MAXINT" << endl;
		errno = 0;
		return 0;
	}

	return doubleFromStr;
}

double DegreesInRadians(double deg)
{
	return (deg * PI / 180);
}

double CalculateDistance(double deg, double velocity)
{
	return (velocity * velocity * sin(2 * DegreesInRadians(deg)) / ACCELERATION_OF_GRAVITY);
}

int main(int argc, char* argv[])
{
	bool timeToEnter = false;
	while (!timeToEnter)
	{
		char v0[SIZE_OF_DATA], a0[SIZE_OF_DATA];
		cout << "Enter v0(or type ‘exit’)>10" << endl;
		cin >> v0;
		string str = v0;
		if (str == "exit")
		{
			cout << "Goodbye!" << endl;
			timeToEnter = true;
		}
		else
		{
			cout << "Enter a0(or type ‘exit’)>30" << endl;
			cin >> a0;
			str = a0;
			if (str == "exit")
			{
				cout << "Goodbye!" << endl;
				timeToEnter = true;
			}
			else
			{
				bool err;
				double rad = StringToDouble(a0, err);
				double velocity = StringToDouble(v0, err);
				cout << "Distance: " << CalculateDistance(rad, velocity) << endl;
			}
		}
	}

	return 0;
}
