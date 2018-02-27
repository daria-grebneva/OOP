#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int NONE_POSITION = 4294967295;

string ChangeString(const string& str, const string& searchStr, const string& replaceStr)
{
	string newStr = "";

	unsigned int foundPos = 0;
	unsigned int currPos = 0;

	for (unsigned int foundPos = 0; foundPos != string::npos; currPos = foundPos + searchStr.size())
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

string ReplaceStrInFile(ifstream& fileIn, ofstream& fileOut, const string& searchStr, const string& replaceStr)
{
	string currentStr = "";
	unsigned int notReplaceCounter = 0;
	unsigned int strNumberCounter = 0;

	while (!fileIn.eof())
	{
		strNumberCounter++;
		string str;
		getline(fileIn, str);

		if (searchStr != "")
		{
			string newString = ChangeString(str, searchStr, replaceStr);
			if (str == newString)
			{
				notReplaceCounter++;
			}
			currentStr += newString;
			currentStr += '\n';
		}
		else
		{
			currentStr += str;
			currentStr += '\n';
		}
	}
	if (strNumberCounter == notReplaceCounter)
	{
		currentStr = "";
	}

	return currentStr;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Please, enter arguments" << endl;
		return 1;
	}

	const string nameInputFile = argv[1];
	const string nameOutputFile = argv[2];
	const string searchStr = argv[3];
	const string replaceStr = argv[4];

	ifstream fileIn(nameInputFile);
	ofstream fileOut(nameOutputFile);

	if (!fileOut.is_open())
	{
		cout << "Output file " << nameOutputFile << " cannot be found or opened" << endl;
		return 1;
	}

	if (fileIn.is_open())
	{
		string str = ReplaceStrInFile(fileIn, fileOut, searchStr, replaceStr);
		if (str == "")
		{
			cout << "This substring does not exist" << endl;
			return 1;
		}
		else
		{
			fileOut << str;
		}
	}
	else
	{
		cout << "Input file " << nameInputFile << " cannot be found or opened" << endl;
		return 1;
	}
	return 0;
}
