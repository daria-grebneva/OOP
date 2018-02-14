#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string ChangeString(string str, string searchStr, string replaceStr)
{
	string newStr = "";

	size_t foundPos = 0;
	size_t currPos = 0;
	for (foundPos = str.find(searchStr, foundPos); foundPos != string::npos; foundPos = str.find(searchStr, foundPos + searchStr.length()))
	{
		newStr.append(str, currPos, foundPos - currPos);
		if (foundPos != std::string::npos)
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

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Please, enter arguments" << endl;
		return 1;
	}

	string nameInputFile = argv[1];
	string nameOutputFile = argv[2];
	string searchStr = argv[3];
	string replaceStr = argv[4];

	ifstream fileIn(nameInputFile);
	ofstream fileOut(nameOutputFile);

	if (!fileOut.is_open())
	{
		cout << "Output file " << nameOutputFile << " cannot be found or opened" << endl;
		return 1;
	}

	if (fileIn.is_open())
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
	else
	{
		cout << "Input file " << nameInputFile << " cannot be found or opened" << endl;
		return 1;
	}
	return 0;
}
