#include "stdafx.h"

#include "decode_HTML.h"

using namespace std;

void Replace(string& str, const string& searchStr, const string& replaceStr)
{
	size_t pos = 0;
	std::string resultStr;
	while (pos < str.length())
	{
		size_t foundPos = str.find(searchStr, pos);
		resultStr.append(str, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			resultStr.append(replaceStr);
			pos = foundPos + searchStr.length();
		}
		else
		{
			break;
		}
	}

	str = resultStr;
}

string ReplaceStr(string str)
{
	string changedStr = "";
	
	if (str == "&quot;")
	{
		changedStr = "\"";
	}
	else if (str == "&apos;")
	{
		changedStr = "'";
	}
	else if (str == "&lt;")
	{
		changedStr = "<";
	}
	else if (str == "&gt;")
	{
		changedStr = ">";
	}
	else if (str == "&amp;")
	{
		changedStr = "&";
	}

	return changedStr;
}

vector<string> GetVectorStrings(vector<string> & vectorStr)
{
	vectorStr.push_back("&quot;");
	vectorStr.push_back("&apos;");
	vectorStr.push_back("&lt;");
	vectorStr.push_back("&gt;");
	vectorStr.push_back("&amp;");
	return vectorStr;
}

string HtmlDecode(string const& html)
{
	string newHtmlStr = html;
	vector<string> vectorStr;
	GetVectorStrings(vectorStr);
	for (auto & elem : vectorStr)
	{
		Replace(newHtmlStr, elem, ReplaceStr(elem));
	}
	return newHtmlStr;
}

int tmain()
{
	string html = "We&quot;";

	cout << HtmlDecode(html);
	return 0;
}
