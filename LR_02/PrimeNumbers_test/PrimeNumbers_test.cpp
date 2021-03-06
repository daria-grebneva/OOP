#include "stdafx.h"
#include "../PrimeNumbers/PrimeNumbers.h"

TEST_CASE("0 and 1 are not prime numbers", "[primeNumbers]")
{
	set<int> primes;
	primes.insert(2);
	CHECK(GetPrimeNumbersSet(2) == primes);
}

TEST_CASE("Return false if upper bound larger than MAX_UPPER_BOUND", "[primeNumbers]")
{
	int upperBound;
	int overflowNumber = MAX_UPPER_BOUND + 1;
	CHECK(!ParseUpperBound(to_string(overflowNumber), upperBound));
}

TEST_CASE("Return false if upper bound not a number", "[primeNumbers]")
{
	int upperBound;
	string inputString = "not2a3number";
	CHECK(!ParseUpperBound(inputString, upperBound));
}

TEST_CASE("Return false if upper bound less than 0", "[primeNumbers]")
{
	int upperBound;
	string inputString = "-13";
	CHECK(!ParseUpperBound(inputString, upperBound));
}

#ifndef _DEBUG
TEST_CASE("5761455 prime numbers in the range up to MAX_UPPER_BOUND", "[primeNumbers]")
{
	auto primeNumbers = GetPrimeNumbersSet(MAX_UPPER_BOUND);
	CHECK(primeNumbers.size() == 5761455);
}
#endif

TEST_CASE("2, 3, 5, 7, 11, 13 are prime numbers in the range up to 13", "[primeNumbers]")
{
	auto primeNumbers = GetPrimeNumbersSet(13);
	CHECK(primeNumbers == set<int>{ 2, 3, 5, 7, 11, 13 });
}
