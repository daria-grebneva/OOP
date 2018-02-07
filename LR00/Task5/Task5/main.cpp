// Task5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cerrno>
#include <cmath>

using namespace std;

const int SIZE_OF_DATA = 200;
const double PI = 3.141592653;
const double ACCELERATION_OF_GRAVITY = 9.8;

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

double degreesInRadians(double deg)
{
	return (deg * PI / 180);
}

double calculateDistance(double deg, double velocity)
{
	return (4 * velocity * velocity /(ACCELERATION_OF_GRAVITY * sin(2 * degreesInRadians(deg))));
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
				cout << "Distance: " << calculateDistance(rad, velocity) << endl;
			}
		}
	}
	
    return 0;
}

