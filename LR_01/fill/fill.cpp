#include "stdafx.h"

#include "fill.h"

using namespace std;

void ShowExampleInput()
{
	cout << "Input data should be like this: " << endl;
	cout << "<input file> <output file>" << endl;
}

void InitOutline(Field& field)
{
	for (int row = 0; row < MAX_SIZE; row++)
	{
		for (int col = 0; col < MAX_SIZE; col++)
		{
			if (row == 0 || row == MAX_SIZE - 1 || col == 0 || col == MAX_SIZE - 1)
			{
				field.outline[row][col] = CellType::WALL;
			}
			else
			{
				field.outline[row][col] = CellType::EMPTY;
			}
		}
	}
}

Size GetOutlineSize(const Field& field)
{
	int maxRow = 0;
	int maxCol = 0;
	for (int row = 1; row < MAX_SIZE - 1; row++)
	{
		for (int col = 1; col < MAX_SIZE - 1; col++)
		{
			if (field.outline[row][col] != CellType::EMPTY)
			{
				maxRow = max(maxRow, row);
				maxCol = max(maxCol, col);
			}
		}
	}

	return Size{ maxRow, maxCol };
}

char EnumToChar(const Field& field, int row, int col)
{
	if (field.outline[row][col] == CellType::EMPTY)
	{
		return ' ';
	}
	else if (field.outline[row][col] == CellType::WALL)
	{
		return '#';
	}
	else if (field.outline[row][col] == CellType::START)
	{
		return 'O';
	}
	else if (field.outline[row][col] == CellType::FILLED)
	{
		return '.';
	}
}

void PrintField(std::ostream& output, const Field& field)
{
	auto size = GetOutlineSize(field);

	for (int row = 1; row <= size.row; row++)
	{
		for (int col = 1; col <= size.col; col++)
		{
			output << EnumToChar(field, row, col);
		}
		output << '\n';
	}
}

void AddStartPositions(int row, int col, stack<Position>& startPositions, Field& field)
{
	if (field.outline[row][col] == CellType::START)
	{
		startPositions.push({ row, col });
	}
}

enum CellType CharToEnum(const string& column, int col)
{
	if (column[col] == ' ')
	{
		return CellType::EMPTY;
	}
	else if (column[col] == '#')
	{
		return CellType::WALL;
	}
	else if (column[col] == 'O')
	{
		return CellType::START;
	}
}

bool ReadOutlineFromFile(const string& inputFileName, stack<Position>& startPositions, Field& field)
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
			field.outline[row + 1][col + 1] = CharToEnum(column, col);
			AddStartPositions(row, col, startPositions, field);
		}
	}

	return true;
}

void FillInOutline(stack<Position>& startPositions, const Position& pos, const Offset& offset, Field& field)
{
	int row = pos.row + offset.row;
	int col = pos.col + offset.col;
	if (field.outline[row][col] == CellType::EMPTY)
	{
		startPositions.push({ row, col });
		field.outline[row][col] = CellType::IN_QUEUE;
	}
}

void FillRemainingOutlines(stack<Position>& startPositions, const Position& pos, Field& field)
{
	for (const auto& offset : OFFSETS)
	{
		FillInOutline(startPositions, pos, offset, field);
	}
}

void Fill(stack<Position>& startPositions, Field& field)
{
	while (!startPositions.empty())
	{
		Position pos = startPositions.top();
		startPositions.pop();

		if (field.outline[pos.row][pos.col] == CellType::IN_QUEUE)
		{
			field.outline[pos.row][pos.col] = CellType::FILLED;
		}
		FillRemainingOutlines(startPositions, pos, field);
	}
}
