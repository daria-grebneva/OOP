#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string ChangeString(const string& str, const string& searchStr, const string& replaceStr)
{
	string newStr = "";

	size_t foundPos = 0;
	size_t currPos = 0;
	for (foundPos = str.find(searchStr, foundPos); foundPos != string::npos; foundPos = str.find(searchStr, foundPos + searchStr.length()))
	{
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

	newStr.append(str, currPos, str.size() - 1);

	return newStr;
}

void ReplaceStrInFile(ifstream& fileIn, ofstream& fileOut, const string& searchStr, const string& replaceStr)
{
	while (!fileIn.eof())
	{
		string str;
		getline(fileIn, str);

		if (searchStr != "")
		{
			string newString = ChangeString(str, searchStr, replaceStr);
			fileOut << newString << endl;
		}
		else
		{
			fileOut << str << endl;
		}
	}
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
		ReplaceStrInFile(fileIn, fileOut, searchStr, replaceStr);
	}
	else
	{
		cout << "Input file " << nameInputFile << " cannot be found or opened" << endl;
		return 1;
	}
	return 0;
}
