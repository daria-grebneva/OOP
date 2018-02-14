#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string ChangeString(string str, string searchStr, string replaceStr)
{
	string newStr = "";
	int searchStrcurrPos = 0;
	int prevPos = 0;
	int currPos = 0;
	bool isFirstIteration = true;

	for (currPos = str.find(searchStr, currPos++); currPos != string::npos; currPos = str.find(searchStr, currPos + 1))
	{
		//если строка начинается без замены
		if ((isFirstIteration) && (currPos != 0))
		{
			for (int i = prevPos; i < currPos; ++i)
			{
				newStr += str[i];
			}
		}

		//вставка кусков строк без замены (между заменами)
		if (!isFirstIteration)
		{
			for (int i = prevPos; i < currPos - searchStr.size(); ++i)
			{
				newStr += str[i + searchStr.size()];
			}
		}

		//замена подстроки
		for (int j = prevPos; j < searchStr.size() + currPos; ++j)
		{
			if (j == currPos + 1)
			{
				newStr += replaceStr;
			}
		}

		prevPos = currPos;
		isFirstIteration = false;
	}

	//если строка закончилась, а символы без замены остались
	if (!isFirstIteration)
	{
		for (int i = prevPos + searchStr.size(); i < str.size(); ++i)
		{
			newStr += str[i];
		}
	}
	else
	{
		newStr = str;
	}

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
