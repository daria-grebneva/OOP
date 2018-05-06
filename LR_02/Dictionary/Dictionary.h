#pragma once

typedef std::multimap<std::string, std::string> Dictionary;

void ProcessEnteredWord(const std::string& word, Dictionary& dictionary, bool& isNewWord);
Dictionary ReadDictionaryFromFile(const std::string& inputFileName);
std::string FindWordInDictionary(const std::string& word, Dictionary& dictionary);
bool SaveNewWord(const std::string& word, Dictionary& dictionary);
void ReadWordAndProcess(Dictionary& dictionary, bool& isNewWord);
void UpdateDictionary(const std::string& inputFileName, Dictionary& dictionary);
