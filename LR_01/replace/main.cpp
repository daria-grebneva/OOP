#include "stdafx.h"

#include "replace.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Please, enter arguments" << endl;
		return 1;
	}

	const string nameInputFile = argv[1];
	const string nameOutputFile = argv[2];
	const string searchStr = argv[3];
	const string replaceStr = argv[4];

	if (!CopyWithReplacement(nameInputFile, nameOutputFile, searchStr, replaceStr))
	{
		cout << "One of the files cannot be found or opened" << endl;
		cout << "Please, check your <input file> and <output file>" << endl;
		return 1;
	}

	return 0;
}