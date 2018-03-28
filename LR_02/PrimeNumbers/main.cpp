#include "stdafx.h"

#include "PrimeNumbers.h"

using namespace std;

void ShowUsage()
{
	cout << "Usage: prime_generator.exe <upper bound>" << endl;
	cout << MIN_UPPER_BOUND << " <= <upper bound> <= " << MAX_UPPER_BOUND << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		ShowUsage();
		return 1;
	}

	int upperBound;
	
	if (!ParseUpperBound(argv[1], upperBound))
	{
		ShowUsage();
		return 1;
	}

	auto primeNumbers = GetPrimeNumbersSet(upperBound);
	PrintPrimeNumbers(primeNumbers);

	return 0;
}
