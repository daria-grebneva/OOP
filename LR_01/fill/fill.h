#pragma once

const int MAX_SIZE = 102;
const int OFFSET_SIZE = 4;
//!!!!
char outline[MAX_SIZE][MAX_SIZE];

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

bool IsTheNumberOfArgumentsCorrect(int argc);
void InitOutline();
bool ReadOutlineFromFile(const std::string& inputFileName, std::stack<Position>& startPositions);
void Fill(std::stack<Position>& startPositions);
void PrintField(std::ostream& output);
void ShowExampleInput();
