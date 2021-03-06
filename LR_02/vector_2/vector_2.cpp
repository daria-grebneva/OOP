#include "stdafx.h"
#include "vector_2.h"

using namespace std;

void ProcessVector(vector<double>& vectorDoubleNumbers)
{
	if (!vectorDoubleNumbers.empty())
	{
		const double MIN_NUMBER = *min_element(vectorDoubleNumbers.begin(), vectorDoubleNumbers.end());
		for (auto& elem : vectorDoubleNumbers)
		{
			elem = elem * MIN_NUMBER;
		}
	}
}

void PrintVector(const vector<double>& vectorDoubleNumbers)
{
	cout << fixed << setprecision(3);
	copy(vectorDoubleNumbers.begin(), vectorDoubleNumbers.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}

vector<double> ReadVector()
{
	return vector<double>(istream_iterator<double>(cin), istream_iterator<double>());
}
