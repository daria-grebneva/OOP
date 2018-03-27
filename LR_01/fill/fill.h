#pragma once

const int MAX_SIZE = 102;
const int OFFSET_SIZE = 4;

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

const Offset Offsets[OFFSET_SIZE] = {
	{ 0, 1 },
	{ 1, 0 },
	{ 0, -1 },
	{ -1, 0 }
};
