#include "stdafx.h"

#include "fill.h"

using namespace std;

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
	if (ReadOutlineFromFile(inputFileName, startPositions))
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
