#include "stdafx.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string Replace(const string& str, const string& searchStr, const string& replaceStr)
{
	string newStr = "";

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

string ReplaceStr(string str)
{
	string changedStr = "";
	
	if (str == "&quot")
	{
		changedStr = "“";
	}
	else if (str == "&apos")
	{
		changedStr = "‘";
	}
	else if (str == "&lt")
	{
		changedStr = "<";
	}
	else if (str == "&gt")
	{
		changedStr = ">";
	}
	else if (str == "&amp")
	{
		changedStr = "&";
	}

	return changedStr;
}

vector<string> GetVectorStrings(vector<string> & vectorStr)
{
	vectorStr.push_back("&quot");
	vectorStr.push_back("&apos");
	vectorStr.push_back("&lt");
	vectorStr.push_back("&gt");
	vectorStr.push_back("&amp");
	return vectorStr;
}

string HtmlDecode(string const& html)
{
	string newHtmlStr = html;
	vector<string> vectorStr;
	GetVectorStrings(vectorStr);
	for (auto & elem : vectorStr)
	{
		Replace(html, elem, ReplaceStr(elem));
	}
}

int main()
{
	string html;
	cin >> html;
	HtmlDecode(html);
	return 0;
}
