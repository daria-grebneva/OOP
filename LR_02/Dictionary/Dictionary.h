#pragma once

using namespace std;
typedef multimap<string, string> Dictionary;
const unsigned ARG_COUNT = 2;

const string EXIT_STRING = "...";

bool IsFileExist(const string& fileName);
void ProcessEnteredWord(const string& word, Dictionary& dictionary, bool& isNewWord);
void ReadDictionaryFromFile(const string& inputFileName, Dictionary& dictionary);
string FindWordInDictionary(const string& word, Dictionary& dictionary);
bool IsNewWordSaved(const string& word, Dictionary& dictionary);
void ReadWordAndProcess(Dictionary& dictionary, bool& isNewWord);
void UpdateDictionary(const string & inputFileName, bool isNewWord, Dictionary& dictionary);
