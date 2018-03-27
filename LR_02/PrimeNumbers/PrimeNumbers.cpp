#include "stdafx.h"

#include "PrimeNumbers.h"

using namespace std;

void RunEratosthenesSieve(int upperBound, vector<bool>& numbers)
{
	for (int i = 2; i * i <= upperBound; ++i)
	{
		if (numbers[i])
		{
			for (int j = i * i; j <= upperBound; j += 2 * i)
			{
				numbers[j] = false;
			}
		}
	}
}

set<int> GetPrimeNumbersToSet(int upperBound, const vector<bool>& numbers)
{
	set<int> primes;
	if (upperBound >= 2)
	{
		primes.insert(2);
	}
	for (int i = 3; i <= upperBound; i += 2)
	{
		if (numbers[i])
		{
			primes.insert(primes.end(), static_cast<int>(i));
		}
	}
	return primes;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> numbers(upperBound + 1, true);
	RunEratosthenesSieve(upperBound, numbers);
	return GetPrimeNumbersToSet(upperBound, numbers);
}

void PrintPrimeNumbers(set<int>& primeNumbers)
{
	copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

void ShowInstruction()
{
	cout << "Usage: prime_generator.exe <upper bound>" << endl;
	cout << MIN_UPPER_BOUND << " <= <upper bound> <= " << MAX_UPPER_BOUND << endl;
}

bool CheckInputNumber(const string& inputString, int& number)
{
	try
	{
		number = stoi(inputString);
		if ((number > MAX_UPPER_BOUND) || (number < MIN_UPPER_BOUND))
		{
			return false;
		}
	}
	catch (const invalid_argument& isError)
	{
		cerr << isError.what() << endl;
		return false;
	}
	catch (const out_of_range& isError)
	{
		cerr << isError.what() << endl;
		return false;
	}

	return true;
}
