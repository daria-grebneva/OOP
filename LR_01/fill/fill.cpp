#include "stdafx.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_SIZE = 102;

char outline[MAX_SIZE][MAX_SIZE];

struct Position
{
	int row;
	int col;
};

void ShowExampleInput()
{
	cout << "Input data should be like this: " << endl;
	cout << "<input file> <output file>" << endl;
}

bool IsTheNumberOfArgumentsCorrect(int argc)
{
	if (argc != 3)
	{
		cout << "The input data is invalid." << endl;
		ShowExampleInput();
		return false;
	}
	return true;
}

void InitOutline()
{
	for (int row = 0; row < MAX_SIZE; row++)
	{
		for (int col = 0; col < MAX_SIZE; col++)
		{
			if (row == 0 || row == MAX_SIZE - 1 || col == 0 || col == MAX_SIZE - 1)
			{
				outline[row][col] = '#';
			}
			else
			{
				outline[row][col] = ' ';
			}
		}
	}
}

Position GetOutlineSize()
{
	int maxRow = 0;
	int maxCol = 0;
	for (int row = 1; row < MAX_SIZE - 1; row++)
	{
		for (int col = 1; col < MAX_SIZE - 1; col++)
		{
			if (outline[row][col] != ' ')
			{
				maxRow = max(maxRow, row);
				maxCol = max(maxCol, col);
			}
		}
	}

	return Position{ maxRow, maxCol };
}

void PrintField(std::ostream& output)
{
	auto size = GetOutlineSize();

	for (int row = 1; row <= size.row; row++)
	{
		for (int col = 1; col <= size.col; col++)
		{
			output << outline[row][col];
		}
		output << '\n';
	}
}

void AddValueToTheOutline(int& row, const string& str, vector<Position>& startCoordinates)
{
	for (int col = 0; col < str.length(); col++)
	{
		outline[row + 1][col + 1] = str[col];
		if (outline[row][col] == 'O')
		{
			startCoordinates.push_back({ row, col });
		}
	}
}

bool OpenFileAndReadOutline(const string& nameInputFile, vector<Position>& startPosition)
{
	ifstream fileIn(nameInputFile);
	if (!fileIn.is_open())
	{
		return false;
	}

	for (int row = 0; (row < MAX_SIZE && (!fileIn.eof())); row++)
	{
		string str;
		getline(fileIn, str);
		AddValueToTheOutline(row, str, startPosition);
	}

	return true;
}

void IncreaseFillPosition(vector<Position>& startPosition, const Position& pos, int rowInc, int colInc)
{
	if (outline[pos.row + rowInc][pos.col + colInc] == ' ')
	{
		startPosition.push_back({ pos.row + rowInc, pos.col + colInc });
		outline[pos.row + rowInc][pos.col + colInc] = '$';
	}
}

void FillRemainingOutlines(vector<Position>& startPosition, const Position& pos)
{
	IncreaseFillPosition(startPosition, pos, 0, 1);
	IncreaseFillPosition(startPosition, pos, 1, 0);
	IncreaseFillPosition(startPosition, pos, 0, -1);
	IncreaseFillPosition(startPosition, pos, -1, 0);
}

void Fill(vector<Position> startPosition)
{
	while (!startPosition.empty())
	{
		Position pos = startPosition.front();
		startPosition.erase(startPosition.begin());

		if (outline[pos.row][pos.col] == '$')
		{
			outline[pos.row][pos.col] = '.';
		}
		FillRemainingOutlines(startPosition, pos);
	}
}

int main(int argc, char* argv[])
{
	if (!IsTheNumberOfArgumentsCorrect(argc))
	{
		return 1;
	}

	string inputFileName = argv[1];
	string outputFileName = argv[2];

	ofstream output(outputFileName);
	InitOutline();
	vector<Position> startPosition;
	if (OpenFileAndReadOutline(inputFileName, startPosition))
	{
		Fill(startPosition);
		PrintField(output);
	}
	else
	{
		ShowExampleInput();
		return 1;
	}
}
