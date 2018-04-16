#include "stdafx.h"

#include "decode_HTML.h"

using namespace std;

const string EXIT_STRING = "...";

int main()
{
	string html;
	cout << "Enter entity or <...> to exit" << endl;
	while (getline(cin, html) && (html != EXIT_STRING))
	{
		cout << HtmlDecode(html) << endl;
	}
	return 0;
}
