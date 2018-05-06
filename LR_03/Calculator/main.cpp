#include "stdafx.h"
#include "CCalculatorController.h"

using namespace std;

int main()
{
	CCalculatorController calculator;
	string command;

	calculator.ShowUsage();

	while (command != EXIT)
	{
		getline(cin, command);

		if (command == EXIT)
		{
			return 0;
		}

		if (command == SHOW_USAGE)
		{
			calculator.ShowUsage();
		}
		else
		{
			calculator.ProcessCommand(command);
		}
	}

	return 0;
}
