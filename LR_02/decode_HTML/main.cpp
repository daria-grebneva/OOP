#include "stdafx.h"

#include "decode_HTML.h"

using namespace std;

int main()
{
	string html = "We&quot;";

	cout << HtmlDecode(html);
	return 0;
}
