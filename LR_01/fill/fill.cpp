#include "stdafx.h"

#include "fill.h"

using namespace std;

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

Size GetOutlineSize()
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

	return Size{ maxRow, maxCol };
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

void AddStartPositions(int row, int col, stack<Position>& startPositions)
{
	if (outline[row][col] == 'O')
	{
		startPositions.push({ row, col });
	}
}

bool OpenFileAndReadOutline(const string& inputFileName, stack<Position>& startPositions)
{
	ifstream fileIn(inputFileName);

	if (!fileIn.is_open())
	{
		return false;
	}

	for (int row = 0; (row < MAX_SIZE && (!fileIn.eof())); row++)
	{
		string column;
		getline(fileIn, column);

		for (int col = 0; col < column.length(); col++)
		{
			outline[row + 1][col + 1] = column[col];
			AddStartPositions(row, col, startPositions);
		}
	}

	return true;
}

void FillInOutline(stack<Position>& startPositions, const Position& pos, Offset offset)
{
	int row = pos.row + offset.row;
	int col = pos.col + offset.col;
	if (outline[row][col] == ' ')
	{
		startPositions.push({ row, col });
		outline[row][col] = '$';
	}
}

void FillRemainingOutlines(stack<Position>& startPositions, const Position& pos)
{
	for (const auto& offset : OFFSETS)
	{
		FillInOutline(startPositions, pos, offset);
	}
}

void Fill(stack<Position>& startPositions)
{
	while (!startPositions.empty())
	{
		Position pos = startPositions.top();
		startPositions.pop();

		if (outline[pos.row][pos.col] == '$')
		{
			outline[pos.row][pos.col] = '.';
		}
		FillRemainingOutlines(startPositions, pos);
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

	stack<Position> startPositions;
	if (OpenFileAndReadOutline(inputFileName, startPositions))
	{
		Fill(startPositions);
		PrintField(output);
	}
	else
	{
		ShowExampleInput();
		return 1;
	}
}
