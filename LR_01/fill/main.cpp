#include "stdafx.h"

#include "fill.h"

using namespace std;

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

int main(int argc, char* argv[])
{
	if (!IsTheNumberOfArgumentsCorrect(argc))
	{
		return 1;
	}

	string inputFileName = argv[1];
	string outputFileName = argv[2];

	ofstream output(outputFileName);
	Field field;
	InitOutline(field);

	stack<Position> startPositions;
	if (ReadOutlineFromFile(inputFileName, startPositions, field))
	{
		Fill(startPositions, field);
		PrintField(output, field);
	}
	else
	{
		ShowExampleInput();
		return 1;
	}
}
