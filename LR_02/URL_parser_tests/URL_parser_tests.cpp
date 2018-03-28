#include "stdafx.h"
#include "../URL_parser/URL_parser.h"

TEST_CASE("ParseURL test", "[parseURL]")
{
	int port;
	string host;
	string document;
	Protocol protocol;
	string url = "http://www.mysite.com:90/docs/document1.html?page=30&lang=en#title";
	CHECK(ParseURL(url, protocol, port, host, document));
	CHECK(port == 90);
	CHECK(port != 80);

	url = "tps://www.mysite.com:90/docs/document1.html?page=30&lang=en#title";
	CHECK(!ParseURL(url, protocol, port, host, document));


	url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	CHECK(ParseURL(url, protocol, port, host, document));
	CHECK(port == 21);

	url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	CHECK(ParseURL(url, protocol, port, host, document));
	CHECK(port == 443);

	url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	CHECK(ParseURL(url, protocol, port, host, document));
	CHECK(port == 80);

	url = "http://www.mysite.com/";
	CHECK(ParseURL(url, protocol, port, host, document));
}
