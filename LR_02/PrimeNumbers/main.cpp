#include "stdafx.h"

#include "PrimeNumbers.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		ShowInstruction();
		return 1;
	}

	int upperBound;
	if (!CheckInputNumber(argv[1], upperBound))
	{
		ShowInstruction();
		return 1;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbers(primeNumbers);

	return 0;
}
