#include "stdafx.h"

using namespace std;

const unsigned int SIZE_OF_MATRIX = 3;

typedef double Matrix3x3[SIZE_OF_MATRIX][SIZE_OF_MATRIX];
typedef double Matrix2x2[SIZE_OF_MATRIX - 1][SIZE_OF_MATRIX - 1];

void PrintMatrix(const Matrix3x3& matrix)
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

int GetNextLine(int currentLine, int line)
{
	return (currentLine > line) ? (currentLine - 1) : currentLine;
}

double FindMinorFromMatrix(const Matrix3x3& minorMatrix)
{
	double minor = minorMatrix[0][0] * minorMatrix[1][1]
		- minorMatrix[1][0] * minorMatrix[0][1];
	return minor;
}

double GetMinorOfMatrix(const Matrix3x3& matrix, int col, int row)
{
	int minorCol;
	int minorRow;
	Matrix3x3 minorMatrix;
	for (int currentCol = 0; currentCol < SIZE_OF_MATRIX; currentCol++)
	{
		if (currentCol == col)
		{
			continue;
		}
		minorCol = GetNextLine(currentCol, col);
		for (int currentRow = 0; currentRow < SIZE_OF_MATRIX; currentRow++)
		{
			if (currentRow == row)
			{
				continue;
			}
			minorRow = GetNextLine(currentRow, row);
			minorMatrix[minorCol][minorRow] = matrix[currentCol][currentRow];
		}
	}

	return FindMinorFromMatrix(minorMatrix);
}

double FindCofactor(double minor, int row, int col)
{
	bool isEvenExpression = (row + col) % 2 == 0;
	return (isEvenExpression) ? minor : -minor;
}

void GetСofactorOfMatrix(const Matrix3x3& matrix, Matrix3x3& cofactorMatrix)
{
	for (int row = 0; row < SIZE_OF_MATRIX; ++row)
	{
		for (int col = 0; col < SIZE_OF_MATRIX; ++col)
		{
			double minor = GetMinorOfMatrix(matrix, row, col);
			cofactorMatrix[row][col] = FindCofactor(minor, row + 1, col + 1);
		}
	}
}

void TransposeMatrix(Matrix3x3& matrix)
{
	for (size_t row = 1; row < SIZE_OF_MATRIX; ++row)
	{
		for (size_t col = 0; col < row; ++col)
		{
			swap(matrix[row][col], matrix[col][row]);
		}
	}
}

double GetDeterminantOfMatrix(const Matrix3x3& matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[1][0] * matrix[2][1] * matrix[0][2]
		+ matrix[2][0] * matrix[0][1] * matrix[1][2]
		- matrix[2][0] * matrix[1][1] * matrix[0][2]
		- matrix[0][0] * matrix[2][1] * matrix[1][2]
		- matrix[1][0] * matrix[0][1] * matrix[2][2];
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

void InvertMatrix(Matrix3x3& matrix, Matrix3x3& cofactorMatrix)
{
	double determinant = GetDeterminantOfMatrix(matrix);
	GetСofactorOfMatrix(matrix, cofactorMatrix);
	DeterminantDivision(cofactorMatrix, determinant);
	TransposeMatrix(cofactorMatrix);
}

bool ReadMatrix(string nameInputFile, Matrix3x3& matrix)
{
	ifstream fileIn(nameInputFile);
	if (!fileIn.is_open())
	{
		return false;
	}
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
