#include "stdafx.h"
#include "../PrimeNumbers/PrimeNumbers.h"

TEST_CASE("0 and 1 are not prime numbers", "[primeNumbers]")
{
	set<int> primes;
	primes.insert(2);
	CHECK(GeneratePrimeNumbersSet(2) == primes);
}

TEST_CASE("Return false if upper bound larger than MAX_UPPER_BOUND", "[primeNumbers]")
{
	int upperBound;
	int overflowNumber = MAX_UPPER_BOUND + 1;
	string inputString = to_string(overflowNumber);
	CHECK(!CheckInputNumber(inputString, upperBound));
}

TEST_CASE("Return false if upper bound not a number", "[primeNumbers]")
{
	int upperBound;
	string inputString = "1not2a3number";
	CHECK(!CheckInputNumber(inputString, upperBound));
}

TEST_CASE("Return false if upper bound less than 0", "[primeNumbers]")
{
	int upperBound;
	string inputString = "-13";
	CHECK(!CheckInputNumber(inputString, upperBound));
}

TEST_CASE("5761455 prime numbers in the range up to MAX_UPPER_BOUND", "[primeNumbers]")
{
	auto primeNumbers = GeneratePrimeNumbersSet(MAX_UPPER_BOUND);
	CHECK(primeNumbers.size() == 5761455);
}

TEST_CASE("2, 3, 5, 7, 11, 13 are prime numbers in the range up to 13", "[primeNumbers]")
{
	auto primeNumbers = GeneratePrimeNumbersSet(13);
	CHECK(primeNumbers == set<int>{2, 3, 5, 7, 11, 13});
}
