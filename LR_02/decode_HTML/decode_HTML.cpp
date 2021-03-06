#include "stdafx.h"

#include "decode_HTML.h"

using namespace std;

void Replace(string& str, const string& searchStr, const string& replaceStr)
{
	size_t pos = 0;
	string resultStr;

	while (pos < str.length())
	{
		size_t foundPos = str.find(searchStr, pos);
		resultStr.append(str, pos, foundPos - pos);

		if (foundPos == std::string::npos)
		{
			break;
		}
		resultStr.append(replaceStr);
		pos = foundPos + searchStr.length();
	}

	str = resultStr;
}

string HtmlDecode(string const& html)
{
	string newHtmlStr = html;

	Replace(newHtmlStr, "&quot;", "\"");
	Replace(newHtmlStr, "&apos;", "'");
	Replace(newHtmlStr, "&lt;", "<");
	Replace(newHtmlStr, "&gt;", ">");
	Replace(newHtmlStr, "&amp;", "&");

	return newHtmlStr;
}
