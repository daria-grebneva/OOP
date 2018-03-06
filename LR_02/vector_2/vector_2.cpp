#include "stdafx.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

void ProcessVector(vector<double>& vectorDoubleNumbers, double minElem)
{
	for (std::vector<double>::iterator it = vectorDoubleNumbers.begin(); it != vectorDoubleNumbers.end(); ++it)
		*it = *it * minElem;
	sort(vectorDoubleNumbers.begin(), vectorDoubleNumbers.end());
}

void PrintVector(const vector<double>& vectorDoubleNumbers)
{
	cout << fixed << setprecision(3);
	copy(vectorDoubleNumbers.begin(), vectorDoubleNumbers.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}

bool ReadVector(vector<double>& vectorDoubleNumbers)
{
	vector<double> vectorNumbers((istream_iterator<double>(cin)), istream_iterator<double>());
	vectorDoubleNumbers = vectorNumbers;
	if (vectorDoubleNumbers.empty())
	{
		return false;
	}
	return true;
}

double minElement(const vector<double>& vectorDoubleNumbers)
{

	return *std::min_element(vectorDoubleNumbers.begin(), vectorDoubleNumbers.end());
}

int main()
{
	vector<double> vectorDoubleNumbers;
	if (!ReadVector(vectorDoubleNumbers))
	{
		cout << "Please, enter your array. Example: " << endl;
		cout << "12.45 8.9 23.44" << endl;
		return 1;
	}
	ProcessVector(vectorDoubleNumbers, minElement(vectorDoubleNumbers));
	PrintVector(vectorDoubleNumbers);

	return 0;
}
