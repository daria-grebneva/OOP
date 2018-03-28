#include "stdafx.h"

#include "Dictionary.h"

using namespace std;

bool IsFileExist(const string& fileName)
{
	bool isExist = false;
	ifstream fin(fileName.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}

bool IsNewWordSaved(const string& word, Dictionary& dictionary)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	string translation;
	getline(cin, translation);

	if (!translation.empty())
	{
		dictionary.insert(make_pair(word, translation));
		cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\"." << endl;
		return true;
	}
	else
	{
		cout << "Слово \"" << word << "\" проигнорировано." << endl;
		return false;
	}
}

void AddEndlToStr(string& str)
{
	if (!str.empty())
	{
		str += "\n";
	}
}

string FindWordInDictionary(const string& word, Dictionary& dictionary)
{
	string translation = "";

	for (const auto& e : dictionary)
	{
		if (e.first == word)
		{
			AddEndlToStr(translation);
			translation += e.second;
		}
		else if (e.second == word)
		{
			AddEndlToStr(translation);
			translation += e.first;
		}
	}

	return translation;
}

void ProcessEnteredWord(const string& word, Dictionary& dictionary, bool& isNewWord)
{
	if (FindWordInDictionary(word, dictionary) == "")
	{
		if (IsNewWordSaved(word, dictionary))
		{
			isNewWord = true;
		}
	}
	else
	{
		cout << FindWordInDictionary(word, dictionary) << endl;
	}
}

void ReadWordAndProcess(Dictionary& dictionary, bool& isNewWord)
{
	string word;
	stringstream buf;
	while (getline(cin, word) && (word != EXIT_STRING))
	{
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		ProcessEnteredWord(word, dictionary, isNewWord);
	}
}

bool IsNeedToSave()
{
	cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом." << endl;
	string answer;
	getline(cin, answer);

	if ((answer == "y") || (answer == "Y"))
	{
		cout << "Изменения сохранены. До свидания." << endl;

		return true;
	}

	cout << "Изменения не были сохранены. До свидания." << endl;

	return false;
}

void UpdateDictionary(const string& inputFileName, bool isNewWord, Dictionary& dictionary)
{
	if (isNewWord)
	{
		if (IsNeedToSave())
		{
			fstream clearFile(inputFileName, ios::out);
			ofstream fout(inputFileName);
			for (const auto& e : dictionary)
			{
				fout << e.first << endl;
				fout << e.second << endl;
			}
		}
	}
}

void ReadDictionaryFromFile(const string& inputFileName, Dictionary& dictionary)
{
	ifstream fin(inputFileName);
	while (!fin.eof())
	{
		string word, translate;
		fin >> word >> translate;
		dictionary.insert(make_pair(word, translate));
	}
}
