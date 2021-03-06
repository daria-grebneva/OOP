#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

static const string EXIT_STRING = "...";

bool SaveNewWord(const string& word, Dictionary& dictionary)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	string translation;
	getline(cin, translation);
	transform(translation.begin(), translation.end(), translation.begin(), ::tolower);

	if (!translation.empty())
	{
		dictionary.emplace(word, translation);
		dictionary.emplace(translation, word);
		cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\"." << endl;
		return true;
	}
	else
	{
		cout << "Слово \"" << word << "\" проигнорировано." << endl;
		return false;
	}
}

string FindWordInDictionary(const string& word, Dictionary& dictionary)
{
	string translation = "";

	for (const auto& wordPair : dictionary)
	{
		if (wordPair.first == word)
		{
			translation += wordPair.second;
			translation.append(" ");
		}
	}

	return translation;
}

void ProcessEnteredWord(const string& word, Dictionary& dictionary, bool& isNewWord)
{
	string translation = FindWordInDictionary(word, dictionary);
	if (translation.empty())
	{
		if (SaveNewWord(word, dictionary))
		{
			isNewWord = true;
		}
	}
	else
	{
		cout << translation << endl;
	}
}

void ReadWordAndProcess(Dictionary& dictionary, bool& isNewWord)
{
	string word;
	while (getline(cin, word) && (word != EXIT_STRING))
	{
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		ProcessEnteredWord(word, dictionary, isNewWord);
	}
}

bool IsNeededToSave()
{
	cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом." << endl;
	string answer;
	getline(cin, answer);

	return ((answer == "y") || (answer == "Y"));
}

void UpdateDictionary(const string& inputFileName, Dictionary& dictionary)
{
	if (IsNeededToSave())
	{
		fstream clearFile(inputFileName, ios::out);
		ofstream fout(inputFileName);
		for (const auto& e : dictionary)
		{
			fout << e.first << endl;
			fout << e.second << endl;
		}
		cout << "Изменения сохранены. До свидания." << endl;
	}
	else
	{
		cout << "Изменения не были сохранены. До свидания." << endl;
	}
}

ifstream TryToOpenFileForReading(const string& inputFileName)
{
	ifstream fin(inputFileName);
	if (!fin.is_open())
	{
		ofstream dictionaryFile(inputFileName);
		ifstream fin(inputFileName);
		return fin;
	}
	return fin;
}

Dictionary ReadDictionaryFromFile(const string& inputFileName)
{
	Dictionary dictionary;
	ifstream fin = TryToOpenFileForReading(inputFileName);
	while (!fin.eof() && !fin.fail())
	{
		string word, translation;
		getline(fin, word);
		getline(fin, translation);
		dictionary.emplace(word, translation);
	}

	return dictionary;
}
