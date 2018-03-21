#include "stdafx.h"

#include "Dictionary.h"

using namespace std;

const unsigned ARG_COUNT = 2;

bool IsValidArgumentsCount(int argc)
{
	return (argc == ARG_COUNT);
}

bool IsFileExist(std::string& fileName)
{
	bool isExist = false;
	std::ifstream fin(fileName.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}

bool IsNewWord(const string& word, MMAP_STRING_STRING& dictionary)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	string translation;
	getline(cin, translation);
	cout << translation << endl;
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

string FindWordInDictionary(const string& word, MMAP_STRING_STRING& dictionary)
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
	if (translation == "")
	{
		return "";
	}
	return translation;
}

void CommunicateWithUser(const string& word, MMAP_STRING_STRING& dictionary, bool& isNewWord)
{
	if (FindWordInDictionary(word, dictionary) == "")
	{
		if (IsNewWord(word, dictionary))
		{
			isNewWord = true;
		}
	}
	else
	{
		cout << FindWordInDictionary(word, dictionary) << endl;
	}
}

bool IsNeedToSave()
{
	cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом." << endl;
	std::string answer;
	getline(cin, answer);
	if ((answer == "y") || (answer == "Y"))
	{
		std::cout << "Изменения сохранены. До свидания." << std::endl;
		return true;
	}

	std::cout << "Изменения не были сохранены. До свидания." << std::endl;

	return false;
}

void ReadDictionaryFromFile(const string& inputFileName, MMAP_STRING_STRING& dictionary)
{
	ifstream fin(inputFileName);
	while (!fin.eof())
	{
		string word, translate;
		fin >> word >> translate;
		dictionary.insert(make_pair(word, translate));
	}
}
