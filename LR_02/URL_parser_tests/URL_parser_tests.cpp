#include "stdafx.h"
#include "../URL_parser/URL_parser.h"

#include <map>
using namespace std;

int port;
string host;
string document;
Protocol protocol;

TEST_CASE("Parse URL", "[parseURL]")
{
	std::string url("https://www.mysite.com/docs/document1.html?page=30&lang=en#title");
	CHECK(ParseURL(url, protocol, port, host, document));
	CHECK(protocol == Protocol::HTTPS);
	CHECK(port == 443);
	CHECK(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("Fails to parse URL with a lack of something", "[parseURL]")
{
	CHECK_FALSE(ParseURL("weeee", protocol, port, host, document));
	CHECK_FALSE(ParseURL("www.mysite.com", protocol, port, host, document));
}
TEST_CASE("Fails to parse port out of bounds", "[parseURL]")
{
	CHECK_FALSE(ParseURL("http://www.mysite.com:65536", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http://www.mysite.com:99999999999999", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http://www.mysite.com:0", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http://www.mysite.com:-1", protocol, port, host, document));
}

TEST_CASE("Parse port with boundary values", "[parseURL]")
{
	CHECK(ParseURL("http://www.mysite.com:1", protocol, port, host, document));
	CHECK(ParseURL("http://www.mysite.com:65535", protocol, port, host, document));
}

TEST_CASE("Check the insensitivity of the URL scheme to the register", "[parseURL]")
{
	CHECK(ParseURL("hTTp://www.mysite.com:1", protocol, port, host, document));
	CHECK(ParseURL("HTTPs://www.mysite.com:1", protocol, port, host, document));
	CHECK(ParseURL("fTp://www.mysite.com:1", protocol, port, host, document));
}

TEST_CASE("Parse URL protocols", "[parseURL]")
{
	CHECK(ParseURL("ftp://www.mysite.com/", protocol, port, host, document));
	CHECK(protocol == Protocol::FTP);

	CHECK(ParseURL("https://www.mysite.com/", protocol, port, host, document));
	CHECK(protocol == Protocol::HTTPS);

	CHECK(ParseURL("http://www.mysite.com/", protocol, port, host, document));
	CHECK(protocol == Protocol::HTTP);
}

TEST_CASE("Parse URL protocols without port", "[parseURL]")
{
	CHECK(ParseURL("ftp://www.mysite.com/", protocol, port, host, document));
	CHECK(port == 21);

	CHECK(ParseURL("https://www.mysite.com/", protocol, port, host, document));
	CHECK(port == 443);

	CHECK(ParseURL("http://www.mysite.com/", protocol, port, host, document));
	CHECK(port == 80);

	CHECK_FALSE(ParseURL("tps://www.mysite.com:90/", protocol, port, host, document));
}

TEST_CASE("Parse URL protocols with port", "[parseURL]")
{
	CHECK(ParseURL("http://www.mysite.com:90/", protocol, port, host, document));
	CHECK(port == 90);
	CHECK(port != 80);
}
