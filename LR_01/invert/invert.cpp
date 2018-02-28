#include "stdafx.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

const unsigned int SIZE_OF_MATRIX = 3;

typedef double Matrix3x3[SIZE_OF_MATRIX][SIZE_OF_MATRIX];
typedef double Matrix2x2[SIZE_OF_MATRIX - 1][SIZE_OF_MATRIX - 1];

bool ReadMatrix(Matrix3x3& matrix, ifstream& fileIn)
{
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			if (!(fileIn >> matrix[i][j]))
			{
				return false;
			}
		}
	}
	return true;
}

void PrintMatrix(Matrix3x3& matrix)
{
	cout << fixed << setprecision(3);
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

double GetMinor2x2Matrix(Matrix3x3& matrix, int col, int row)
{
	int minorCol;
	int minorRow;
	Matrix3x3 matrix2x2;
	for (int currentCol = 0; currentCol < SIZE_OF_MATRIX; currentCol++)
	{
		if (currentCol == col)
		{
			continue;
		}
		if (currentCol > col)
		{
			minorCol = currentCol - 1;
		}
		else
		{
			minorCol = currentCol;
		}
		for (int currentRow = 0; currentRow < SIZE_OF_MATRIX; currentRow++)
		{
			if (currentRow == row)
			{
				continue;
			}
			if (currentRow > row)
			{
				minorRow = currentRow - 1;
			}
			else
			{
				minorRow = currentRow;
			}
			matrix2x2[minorCol][minorRow] = matrix[currentCol][currentRow];
		}
	}
	double minor = matrix2x2[0][0] * matrix2x2[1][1]
		- matrix2x2[1][0] * matrix2x2[0][1];
	return minor;
}

double GetСofactor2x2Matrix(double& minor, int minorF, int minorS)
{
	//домножать на -1 в зависимости от нечетности minorF + minorS
	double сofactor = pow(-1, minorF + minorS) * minor;
	return сofactor;
}

void GetСofactor3x3Matrix(Matrix3x3& matrix, Matrix3x3& algebraicComplementsMatrix)
{
	for (size_t row = 0; row < SIZE_OF_MATRIX; ++row)
	{
		for (size_t col = 0; col < SIZE_OF_MATRIX; ++col)
		{
			double minor = GetMinor2x2Matrix(matrix, row, col);
			algebraicComplementsMatrix[row][col] = GetСofactor2x2Matrix(minor, row + 1, col + 1);
		}
	}
}

void MatrixTranspose(Matrix3x3& matrix)
{
	for (size_t row = 1; row < SIZE_OF_MATRIX; ++row)
	{
		for (size_t col = 0; col < row; ++col)
		{
			swap(matrix[row][col], matrix[col][row]);
		}
	}
}

double GetDeterminant3x3Matrix(Matrix3x3& matrix)
{
	double determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] + 
		matrix[1][0] * matrix[2][1] * matrix[0][2] + 
		matrix[2][0] * matrix[0][1] * matrix[1][2] - 
		matrix[2][0] * matrix[1][1] * matrix[0][2] - 
		matrix[0][0] * matrix[2][1] * matrix[1][2] - 
		matrix[1][0] * matrix[0][1] * matrix[2][2];

	return determinant;
}

void DeterminantDivision(Matrix3x3& matrix, double determinant)
{
	for (size_t i = 0; i < SIZE_OF_MATRIX; ++i)
	{
		for (size_t j = 0; j < SIZE_OF_MATRIX; ++j)
		{
			matrix[i][j] = matrix[i][j] / determinant;
		}
	}
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
		MatrixTranspose(algebraicComplementsMatrix);
		PrintMatrix(algebraicComplementsMatrix);
	}
	else
	{
		cout << "Input file " << nameInputFile << " cannot be found or opened" << endl;
		return 1;
	}
	return 0;
}
