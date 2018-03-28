#include "stdafx.h"

#include "PrimeNumbers.h"

using namespace std;

vector<bool> GetEratosthenesSieve(int upperBound)
{
	vector<bool> numbers(upperBound + 1, true);
	for (int i = 2; i * i <= upperBound; ++i)
	{
		if (numbers[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				numbers[j] = false;
			}
		}
	}
	return numbers;
}

set<int> GetPrimeNumbersSet(int upperBound)
{
	set<int> primes;

	auto numbers = GetEratosthenesSieve(upperBound);

	for (int i = 2; i < numbers.size(); i++)
	{
		if (numbers[i])
		{
			primes.insert(primes.end(), static_cast<int>(i));
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

