#pragma once

static const int MAX_SIZE = 102;
static const int OFFSET_SIZE = 4;

struct Position
{
	int row;
	int col;
};

struct Size
{
	int row;
	int col;
};

struct Offset
{
	int row;
	int col;
};

const Offset OFFSETS[OFFSET_SIZE] = {
	{ 0, 1 },
	{ 1, 0 },
	{ 0, -1 },
	{ -1, 0 }
};

enum CellType : char
{
	EMPTY = ' ',
	WALL = '#',
	START = 'O',
	FILLED = '.',
	IN_QUEUE = '$',
};

struct Field
{
	CellType outline[MAX_SIZE][MAX_SIZE];
};

void InitOutline(Field& field);
bool ReadOutlineFromFile(const std::string& inputFileName, std::stack<Position>& startPositions, Field& field);
void Fill(std::stack<Position>& startPositions, Field& field);
void PrintField(std::ostream& output, const Field& field);
void ShowExampleInput();
