#include "stdafx.h"

#include "PrimeNumbers.h"

using namespace std;

vector<bool> GetEratosthenesSieve(int upperBound)
{
	vector<bool> primeNumbers(upperBound + 1, true);
	for (int i = 2; i * i <= upperBound; ++i)
	{
		if (primeNumbers[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				primeNumbers[j] = false;
			}
		}
	}
	return primeNumbers;
}

set<int> GetPrimeNumbersSet(int upperBound)
{
	set<int> primes;

	auto primeNumbers = GetEratosthenesSieve(upperBound);

	for (int i = 2; i < primeNumbers.size(); i++)
	{
		if (primeNumbers[i])
		{
			primes.insert(primes.end(), i);
		}
	}

	return primes;
}

void PrintPrimeNumbers(const set<int>& primeNumbers)
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
