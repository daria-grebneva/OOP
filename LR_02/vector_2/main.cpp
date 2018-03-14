#include "stdafx.h"
#include "vector_2.h"

using namespace std;

int main()
{
	vector<double> vectorDoubleNumbers;
	ReadVector(vectorDoubleNumbers);
	ProcessVector(vectorDoubleNumbers);
	sort(vectorDoubleNumbers.begin(), vectorDoubleNumbers.end());
	PrintVector(vectorDoubleNumbers);

	return 0;
}