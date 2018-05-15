#include "stdafx.h"
#include "CHttpUrl.h"

using namespace std;

int main()
{
	while (!cin.eof() && !cin.fail())
	{
		string inputUrl;
		cout << "Enter URL: ";
		cin >> inputUrl;
		cout << endl;
		try
		{
			CHttpUrl url(inputUrl);
			cout << "> Protocol: " << url.GetProtocolTitle() << endl;
			cout << "> Domain: " << url.GetDomain() << endl;
			cout << "> Port: " << url.GetPort() << endl;
			cout << "> Document: " << url.GetDocument() << endl;
		}
		catch (CUrlParsingError const& e)
		{
			cerr << e.what();
		}
	}

	return 0;
}
