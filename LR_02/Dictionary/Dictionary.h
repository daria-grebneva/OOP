#pragma once

using namespace std;
typedef multimap<string, string> Dictionary;

void ProcessEnteredWord(const string& word, Dictionary& dictionary, bool& isNewWord);
Dictionary ReadDictionaryFromFile(const string& inputFileName);
string FindWordInDictionary(const string& word, Dictionary& dictionary);
bool IsNewWordSaved(const string& word, Dictionary& dictionary);
void ReadWordAndProcess(Dictionary& dictionary, bool& isNewWord);
void UpdateDictionary(const string& inputFileName, Dictionary& dictionary);
bool IsNeedToUpdate(bool isNewWord);
