#include "stdafx.h"

#include "PrimeNumbers.h"

using namespace std;

vector<bool> GetEratosthenesSieve(int upperBound)
{
	vector<bool> isPrimeNumber(upperBound + 1, true);
	for (int i = 2; i * i <= upperBound; ++i)
	{
		if (isPrimeNumber[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				isPrimeNumber[j] = false;
			}
		}
	}
	return isPrimeNumber;
}

set<int> GetPrimeNumbersSet(int upperBound)
{
	set<int> primes;

	auto isPrimeNumber = GetEratosthenesSieve(upperBound);

	for (int i = 2; i < isPrimeNumber.size(); i++)
	{
		if (isPrimeNumber[i])
		{
			primes.insert(primes.end(), i);
		}
	}

	return primes;
}

void PrintPrimeNumbers(set<int>& primeNumbers)
{
	copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

bool UpperBoundIsValid(int number)
{
	return ((MIN_UPPER_BOUND <= number) && (number <= MAX_UPPER_BOUND));
}

bool ParseUpperBound(const string& inputString, int& number)
{
	try
	{
		number = stoi(inputString);
		return UpperBoundIsValid(number);
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return false;
	}
}
