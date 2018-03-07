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

void ReadVector(vector<double>& vectorDoubleNumbers)
{
	vector<double> vectorNumbers((istream_iterator<double>(cin)), istream_iterator<double>());
	vectorDoubleNumbers = vectorNumbers;
}

double minElement(const vector<double>& vectorDoubleNumbers)
{

	return *min_element(vectorDoubleNumbers.begin(), vectorDoubleNumbers.end());
}

int main()
{
	vector<double> vectorDoubleNumbers;
	vectorDoubleNumbers.push_back(0.0);
	ReadVector(vectorDoubleNumbers);
	ProcessVector(vectorDoubleNumbers, minElement(vectorDoubleNumbers));
	PrintVector(vectorDoubleNumbers);

	return 0;
}
