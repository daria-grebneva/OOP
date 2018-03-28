#include "stdafx.h"

#include "URL_parser.h"

using namespace std;


int main()
{
	try
	{
		ParseURLs();
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "Unknown exception" << endl;
		return 1;
	}

	return 0;
}
