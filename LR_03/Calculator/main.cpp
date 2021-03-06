#include "stdafx.h"
#include "CCalculatorController.h"

using namespace std;

int main()
{
	CCalculatorController calculator(cin, cout);
	string command;

	calculator.ShowUsage();
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!calculator.ProcessCommand())
		{
			return 0;
		}
	}
}
