#include "stdafx.h"

using namespace std;

string Replace(const string& str, const string& searchStr, const string& replaceStr)
{
	string newStr = "";

	size_t currPos = 0;

	for (size_t foundPos = 0; foundPos != string::npos; currPos = foundPos + searchStr.size())
	{
		foundPos = str.find(searchStr, currPos);
		newStr.append(str, currPos, foundPos - currPos);

		if (foundPos != string::npos)
		{
			newStr.append(replaceStr);
			currPos = foundPos + searchStr.length();
		}
		else
		{
			break;
		}
	}

	return newStr;
}

string ReplaceStrInFile(ifstream& fileIn, const string& searchStr, const string& replaceStr)
{
	string currentStr = "";

	while (!fileIn.eof())
	{
		string str;
		getline(fileIn, str);

		if (!searchStr.empty())
		{
			string newString = Replace(str, searchStr, replaceStr);
			currentStr += newString;
			currentStr += '\n';
		}
		else
		{
			currentStr += str;
			currentStr += '\n';
		}
	}

	return currentStr;
}

bool CopyWithReplacement(const string& nameInputFile, const string& nameOutputFile, const string& searchStr, const string& replaceStr)
{

	ifstream fileIn(nameInputFile);
	ofstream fileOut(nameOutputFile);

	if ((!fileOut.is_open()) || (!fileIn.is_open()))
	{
		return false;
	}
	else
	{
		string str = ReplaceStrInFile(fileIn, searchStr, replaceStr);
		fileOut << str;
	}

	return true;
}
