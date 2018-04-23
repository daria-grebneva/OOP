#include "stdafx.h"
#include "CalculatorController.h"
#include "Function.h"
#include "Variable.h"

using namespace std;

int main()
{
	CVariable variable;
	CFunction function(&variable);
	CCalculatorController calculator(&variable, &function);
	string command;

	calculator.ShowUsage();

	while (command != EXIT)
	{
		getline(cin, command);

		if (command == EXIT)
		{
			break;
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
