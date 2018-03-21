#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::locale::global(std::locale("rus"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (!IsValidArgumentsCount(argc))
	{
		cout << "Wrong number of arguments" << endl;
		return 1;
	}
	string inputFileName = argv[1];
	if (!IsFileExist(inputFileName))
	{
		cout << "Dictionary file was not found" << endl;
		return 1;
	}

	MMAP_STRING_STRING dictionary;

	ReadDictionaryFromFile(inputFileName, dictionary);

	string word;
	bool isNewWord = false;
	stringstream buf;
	while (getline(cin, word) && (word != EXIT_STRING))
	{
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		CommunicateWithUser(word, dictionary, isNewWord);
	}

	if (isNewWord)
	{
		if (IsNeedToSave())
		{
			fstream clear_file(inputFileName, ios::out);
			ofstream fout(inputFileName);
			for (const auto& e : dictionary)
			{
				fout << e.first << endl;
				fout << e.second << endl;
			}
		}
	}
}
