#include "stdafx.h"
#include "../HTTP_URL/CHttpUrl.h"
#include "../HTTP_URL/CUrlParsingError.h"

using namespace std;
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
			CHttpUrl url("http://mysite.com:800/some_document");
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetProtocolTitle() == "http");
			REQUIRE(url.GetPort() == 800);
			REQUIRE(url.GetDocument() == "/some_document");
			REQUIRE(url.GetDomain() == "mysite.com");
			REQUIRE(url.GetURL() == "http://mysite.com:800/some_document");
		}
		SECTION("Https protocol")
		{
			CHttpUrl url("https://mysite.com:800/some_document");
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
		SECTION("Ports")
		{
			SECTION("Port 80 for http protocol")
			{
				CHttpUrl url("http://mysite.com/some_document");
				REQUIRE(url.GetProtocol() == Protocol::HTTP);
			}
			SECTION("Port 443 for https protocol")
			{
				CHttpUrl url("https://mysite.com:800/some_document");
				REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			}
		}
		SECTION("Url string")
		{
			SECTION("Get url string")
			{
				CHttpUrl url("http://mysite.com:800/some_document");
				REQUIRE(url.GetURL() == "http://mysite.com:800/some_document");
			}
			SECTION("Get url string without port")
			{
				CHttpUrl url("https://mysite.com/some_document");
				REQUIRE(url.GetProtocol() == Protocol::HTTPS);
				REQUIRE(url.GetPort() == 443);
				REQUIRE(url.GetURL() == "https://mysite.com/some_document");

				CHttpUrl newUrl("http://mysite.com/some_document");
				REQUIRE(newUrl.GetProtocol() == Protocol::HTTP);
				REQUIRE(newUrl.GetPort() == 80);
				REQUIRE(newUrl.GetURL() == "http://mysite.com/some_document");
			}
		}
	}
	SECTION("Construct Url")
	{
		SECTION("Domain and document")
		{
			CHttpUrl url("mysite.com", "some_document");
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "mysite.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/some_document");
		}
		SECTION("Domain and document and protocol")
		{
			CHttpUrl url("mysite.com", "some_document", Protocol::HTTP);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "mysite.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/some_document");

			CHttpUrl newUrl("mysite.com", "some_document", Protocol::HTTPS);
			REQUIRE(newUrl.GetProtocol() == Protocol::HTTPS);
			REQUIRE(newUrl.GetDomain() == "mysite.com");
			REQUIRE(newUrl.GetPort() == 443);
			REQUIRE(newUrl.GetDocument() == "/some_document");
		}
		SECTION("Domain and document and protocol and port")
		{
			CHttpUrl url("mysite.com", "some_document", Protocol::HTTP, 880);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "mysite.com");
			REQUIRE(url.GetPort() == 880);
			REQUIRE(url.GetDocument() == "/some_document");

			CHttpUrl newUrl("mysite.com", "some_document", Protocol::HTTPS, 880);
			REQUIRE(newUrl.GetProtocol() == Protocol::HTTPS);
			REQUIRE(newUrl.GetDomain() == "mysite.com");
			REQUIRE(newUrl.GetPort() == 880);
			REQUIRE(newUrl.GetDocument() == "/some_document");
		}
	}
}
