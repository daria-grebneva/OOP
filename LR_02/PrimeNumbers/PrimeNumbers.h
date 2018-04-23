#pragma once

using namespace std;

const int MAX_UPPER_BOUND = 100000000;
const int MIN_UPPER_BOUND = 2;

bool ParseUpperBound(const string& inputString, int& number);
set<int> GetPrimeNumbersSet(int upperBound);
void PrintPrimeNumbers(const set<int>& primeNumbers);
