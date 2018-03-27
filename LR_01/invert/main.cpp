#include "stdafx.h"

#include "invert.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Please, enter arguments" << endl;
		return 1;
	}

	Matrix3x3 matrix;

	if (ReadMatrix(argv[1], matrix))
	{
		Matrix3x3 cofactorMatrix;
		InvertMatrix(matrix, cofactorMatrix);
		PrintMatrix(cofactorMatrix);
	}
	else
	{
		cout << "Input file " << argv[1] << " cannot be found or opened" << endl;
		return 1;
	}

	return 0;
}
