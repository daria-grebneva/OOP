#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>

using namespace std;

const unsigned int SIZE_OF_MATRIX = 3;

typedef double Matrix3x3[SIZE_OF_MATRIX][SIZE_OF_MATRIX];
typedef double Matrix2x2[SIZE_OF_MATRIX - 1][SIZE_OF_MATRIX - 1];

struct Matrix {
	Matrix3x3 matrix;
};

bool ReadMatrix(Matrix3x3& matrix, ifstream& fileIn)
{
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			if (fileIn.eof())
			{
				return false;
			}
			double element;
			fileIn >> element;
			matrix[i][j] = element;
		}
	}
	return true;
}

void PrintMatrix(Matrix3x3& matrix)
{
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			cout << fixed << setprecision(3) << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

double GetMinor2x2Matrix(Matrix3x3& matrix, int colF, int rowF, int colS, int rowS)
{
	double minor = matrix[colF][rowF] * matrix[colS][rowS]
		- matrix[colS][rowF] * matrix[colF][rowS];
	return minor;
}

double GetСofactor2x2Matrix(double& minor, int minorF, int minorS)
{
	double сofactor = pow(-1, minorF + minorS) * minor;
	return сofactor;
}

void GetСofactor3x3Matrix(Matrix3x3& matrix, Matrix3x3 & algebraicComplementsMatrix)
{
	double minor = GetMinor2x2Matrix(matrix, 1, 1, 2, 2);
	algebraicComplementsMatrix[0][0] = GetСofactor2x2Matrix(minor, 1, 1);
	minor = GetMinor2x2Matrix(matrix, 0, 1, 2, 2);
	algebraicComplementsMatrix[0][1] = GetСofactor2x2Matrix(minor, 1, 2);
	minor = GetMinor2x2Matrix(matrix, 0, 1, 1, 2);
	algebraicComplementsMatrix[0][2] = GetСofactor2x2Matrix(minor, 1, 3);
	minor = GetMinor2x2Matrix(matrix, 1, 0, 2, 2);
	algebraicComplementsMatrix[1][0] = GetСofactor2x2Matrix(minor, 2, 1);
	minor = GetMinor2x2Matrix(matrix, 0, 0, 2, 2);
	algebraicComplementsMatrix[1][1] = GetСofactor2x2Matrix(minor, 2, 2);
	minor = GetMinor2x2Matrix(matrix, 0, 0, 1, 2);
	algebraicComplementsMatrix[1][2] = GetСofactor2x2Matrix(minor, 2, 3);
	minor = GetMinor2x2Matrix(matrix, 1, 0, 2, 1);
	algebraicComplementsMatrix[2][0] = GetСofactor2x2Matrix(minor, 3, 1);
	minor = GetMinor2x2Matrix(matrix, 0, 0, 2, 1);
	algebraicComplementsMatrix[2][1] = GetСofactor2x2Matrix(minor, 3, 2);
	minor = GetMinor2x2Matrix(matrix, 0, 0, 1, 1);
	algebraicComplementsMatrix[2][2] = GetСofactor2x2Matrix(minor, 3, 3);
}

double GetDeterminant3x3Matrix(Matrix3x3& matrix)
{
	double determinant = 0;
	determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] + 
		matrix[1][0] * matrix[2][1] * matrix[0][2] + 
		matrix[2][0] * matrix[0][1] * matrix[1][2] - 
		matrix[2][0] * matrix[1][1] * matrix[0][2] - 
		matrix[0][0] * matrix[2][1] * matrix[1][2] - 
		matrix[1][0] * matrix[0][1] * matrix[2][2];
	return determinant;
}

void DeterminantDivision(Matrix3x3 & matrix, double determinant)
{
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			matrix[i][j] = matrix[i][j] / determinant;
		}
	}
}

Matrix MatrixTranspose(Matrix3x3& matrix)
{
	Matrix transponate;
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			transponate.matrix[i][j] = matrix[j][i];
		}
	}

	return transponate;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Please, enter arguments" << endl;
		return 1;
	}
	const string nameInputFile = argv[1];
	ifstream fileIn(nameInputFile);
	if (fileIn.is_open())
	{
		Matrix3x3 matrix;
		Matrix3x3 algebraicComplementsMatrix;
		ReadMatrix(matrix, fileIn);
		double determinant = GetDeterminant3x3Matrix(matrix);
		GetСofactor3x3Matrix(matrix, algebraicComplementsMatrix);
		DeterminantDivision(algebraicComplementsMatrix, determinant);
		PrintMatrix(algebraicComplementsMatrix);
	}
	else
	{
		cout << "Input file " << nameInputFile << " cannot be found or opened" << endl;
		return 1;
	}
	return 0;
}
