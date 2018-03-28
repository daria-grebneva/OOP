#pragma once

const unsigned int SIZE_OF_MATRIX = 3;

typedef double Matrix3x3[SIZE_OF_MATRIX][SIZE_OF_MATRIX];
typedef double Matrix2x2[SIZE_OF_MATRIX - 1][SIZE_OF_MATRIX - 1];

bool ReadMatrix(std::string nameInputFile, Matrix3x3& matrix);
void PrintMatrix(const Matrix3x3& matrix);
void InvertMatrix(Matrix3x3& matrix, Matrix3x3& cofactorMatrix);
