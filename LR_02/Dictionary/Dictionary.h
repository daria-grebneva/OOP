#pragma once

#include "stdafx.h";

using namespace std;
typedef multimap<string, string> MMAP_STRING_STRING;

const string EXIT_STRING = "...";

bool IsValidArgumentsCount(int argc);
bool IsFileExist(std::string& fileName);
void CommunicateWithUser(const string& word, MMAP_STRING_STRING& dictionary, bool& isNewWord);
bool IsNeedToSave();
void ReadDictionaryFromFile(const string& inputFileName, MMAP_STRING_STRING& dictionary);
string FindWordInDictionary(const string& word, MMAP_STRING_STRING& dictionary);
bool IsNewWord(const string& word, MMAP_STRING_STRING& dictionary);
