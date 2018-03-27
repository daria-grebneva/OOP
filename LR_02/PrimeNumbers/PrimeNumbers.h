#pragma once

using namespace std;

const int MAX_UPPER_BOUND = 100000000;
const int MIN_UPPER_BOUND = 2;

bool CheckInputNumber(const string& inputString, int& number);
void ShowInstruction();
set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimeNumbers(set<int>& primeNumbers);
