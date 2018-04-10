#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

static const unsigned ARG_COUNT = 2;
int main(int argc, char* argv[])
{
	std::locale::global(std::locale("rus"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != ARG_COUNT)
	{
		cout << "Please enter the name of the dictionary: <dictionary.txt>" << endl;
		return 1;
	}

	string inputFileName = argv[1];

	bool isNewWord = false;

	Dictionary dictionary = ReadDictionaryFromFile(inputFileName);
	ReadWordAndProcess(dictionary, isNewWord);
	if (IsNeedToUpdate(isNewWord))
	{
		UpdateDictionary(inputFileName, dictionary);
	}

	return 0;
}
