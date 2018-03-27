#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

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

	if (!IsFileExist(inputFileName))
	{
		ofstream dictionaryFile(inputFileName);
	}

	Dictionary dictionary;
	bool isNewWord = false;

	ReadDictionaryFromFile(inputFileName, dictionary);
	ReadWordAndProcess(dictionary, isNewWord);
	UpdateDictionary(inputFileName, isNewWord, dictionary);

	return 0;
}
