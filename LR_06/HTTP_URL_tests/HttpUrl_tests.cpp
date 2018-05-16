#include "stdafx.h"
#include "../HTTP_URL/CHttpUrl.h"
#include "../HTTP_URL/CUrlParsingError.h"

using namespace std;

void CheckUrlParameters(const CHttpUrl& url, Protocol protocol, unsigned short port, string const& document, string const& domain)
{
	REQUIRE(url.GetProtocol() == protocol);
	REQUIRE(url.GetPort() == port);
	REQUIRE(url.GetDocument() == document);
	REQUIRE(url.GetDomain() == domain);
}

void ConstructUrlFromString(string const& inputUrl, Protocol protocol, unsigned short port, string const& document, string const& domain)
{
	CHttpUrl url(inputUrl);
	CheckUrlParameters(url, protocol, port, document, domain);
	REQUIRE(url.GetURL() == inputUrl);
}

void ConstructUrlWithTwoParameters(Protocol protocol, unsigned short port, string const& document, string const& domain)
{
	CHttpUrl url(domain, document);
	CheckUrlParameters(url, protocol, port, document, domain);
}

void ConstructUrlWithThreeParameters(Protocol protocol, unsigned short port, string const& document, string const& domain)
{
	CHttpUrl url(domain, document, protocol);
	CheckUrlParameters(url, protocol, port, document, domain);
}

void ConstructUrlWithFourParameters(Protocol protocol, unsigned short port, string const& document, string const& domain)
{
	CHttpUrl url(domain, document, protocol, port);
	REQUIRE(url.GetProtocol() == protocol);
	REQUIRE(url.GetDomain() == domain);
	REQUIRE(url.GetPort() == port);
	REQUIRE(url.GetDocument() == document);
}

TEST_CASE(" ", "[HTTP Url]")
{
	SECTION("Exceptions")
	{
		SECTION("Protocol is empty")
		{
			REQUIRE_THROWS_AS(CHttpUrl("://mysite.com/document"), std::invalid_argument);
		}
		SECTION("Invalid protocol")
		{
			REQUIRE_THROWS_AS(CHttpUrl("ftp://mysite.com/document"), std::invalid_argument);
		}
		SECTION("Construct with empty arguments")
		{
			REQUIRE_THROWS_AS(CHttpUrl("", "", Protocol::HTTP, 300), std::invalid_argument);
			REQUIRE_THROWS_AS(CHttpUrl("", "document"), std::invalid_argument);
		}
		SECTION("Url without '/'")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http/mysite.com/document"), std::invalid_argument);
			REQUIRE_THROWS_AS(CHttpUrl("http:mysite.com/document"), std::invalid_argument);
		}
		SECTION("Without domain")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http///document"), std::invalid_argument);
		}
		SECTION("With invalid domain")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http//*!MW/document"), std::invalid_argument);
		}
		SECTION("Without port")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http//mysite.com:/document"), std::invalid_argument);
		}
		SECTION("With port out of range")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http//mysite.com:0/document"), std::invalid_argument);
			REQUIRE_THROWS_AS(CHttpUrl("http//mysite.com:65536/document"), std::invalid_argument);
			REQUIRE_THROWS_AS(CHttpUrl("http//mysite.com:99999999999999999999999999/document"), std::invalid_argument);
			REQUIRE_THROWS_AS(CHttpUrl("http//mysite.com:-1/document"), std::invalid_argument);
		}
	}

	SECTION("Get data from Url")
	{
		SECTION("Http protocol")
		{
			ConstructUrlFromString("http://mysite.com:800/some_document", Protocol::HTTP, 800, "/some_document", "mysite.com");
		}
		SECTION("Https protocol")
		{
			ConstructUrlFromString("https://mysite.com:800/some_document", Protocol::HTTPS, 800, "/some_document", "mysite.com");
		}
		SECTION("Ports")
		{
			SECTION("Port 80 for http protocol")
			{
				ConstructUrlFromString("http://mysite.com/some_document", Protocol::HTTP, 80, "/some_document", "mysite.com");
			}
			SECTION("Port 443 for https protocol")
			{
				ConstructUrlFromString("https://mysite.com/some_document", Protocol::HTTPS, 443, "/some_document", "mysite.com");
			}
		}
		SECTION("Url string")
		{
			SECTION("Get url string without port")
			{
				ConstructUrlFromString("https://mysite.com/some_document", Protocol::HTTPS, 443, "/some_document", "mysite.com");
				ConstructUrlFromString("http://mysite.com/some_document", Protocol::HTTP, 80, "/some_document", "mysite.com");
			}
		}
	}
	SECTION("Construct Url")
	{
		SECTION("Domain and document")
		{
			ConstructUrlWithTwoParameters(Protocol::HTTP, 80, "/some_document", "mysite.com");
		}
		SECTION("Domain and document and protocol")
		{
			ConstructUrlWithThreeParameters(Protocol::HTTP, 80, "/some_document", "mysite.com");
			ConstructUrlWithThreeParameters(Protocol::HTTPS, 443, "/some_document", "mysite.com");
		}
		SECTION("Domain and document and protocol and port")
		{
			ConstructUrlWithFourParameters(Protocol::HTTP, 880, "/some_document", "mysite.com");
			ConstructUrlWithFourParameters(Protocol::HTTPS, 880, "/some_document", "mysite.com");
		}
	}
}
