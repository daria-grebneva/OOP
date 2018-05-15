#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

CHttpUrl::CHttpUrl(const string& url)
	: m_url(url)
{

	if (url.empty())
	{
		throw CUrlParsingError("Url is empty\n");
	}
	smatch result;
	regex reg(R"(^(\w+):\/\/([^\s:\/]+)(?::(\d+))?(?:\/(\S*))?$)", regex::icase);
	bool mapped = regex_search(url, result, reg);

	if (!mapped)
	{
		throw CUrlParsingError("Invalid url\n");
	}

	FillProtocolMap();

	m_protocol = ParseProtocol(result[1]);
	m_domain = ParseDomain(result[2]);
	m_port = ParsePort(result[3]);
	m_document = ParseDocument(result[4]);
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol)
	: m_domain(domain)
	, m_document(document)
	, m_protocol(protocol)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Empty domain\n");
	}

	m_document = ParseDocument(document);
	FillProtocolMap();
	string protocolStr;
	if (m_protocol == Protocol::HTTP)
	{
		protocolStr = "http://";
		m_port = Protocol::HTTP;
	}
	else
	{
		protocolStr = "https://";
		m_port = Protocol::HTTPS;
	}

	m_url = protocolStr + m_domain + m_document;
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, unsigned short port)
	: m_domain(domain)
	, m_document(document)
	, m_protocol(protocol)
	, m_port(port)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Empty domain\n");
	}

	m_document = ParseDocument(document);
	FillProtocolMap();

	string portStr = "";
	string protocolStr;
	if (m_protocol == Protocol::HTTP)
	{
		protocolStr = "http://";
		if (m_port != Protocol::HTTP)
		{
			portStr = ":" + to_string(m_port);
		}
	}
	else
	{
		protocolStr = "https://";
		if (m_port != Protocol::HTTPS)
		{
			portStr = ":" + to_string(m_port);
		}
	}

	m_url = protocolStr + m_domain + portStr + m_document;
}

unsigned short CHttpUrl::ParsePort(const string& portString)
{
	unsigned short port = static_cast<unsigned short>(m_protocol);
	if (portString.empty())
	{
		return static_cast<unsigned short>(m_protocol);
	}
	port = stoi(portString);
	if (CheckPortInRange(port))
	{
		return port;
	}
	else
	{
		throw CUrlParsingError("Port out of range\n");
	}
}

string CHttpUrl::ParseDocument(const string& document)
{
	if (document.empty() || (document[0] != '/'))
	{
		return "/" + document;
	}
	return document;
}

bool CHttpUrl::CheckPortInRange(unsigned short port)
{
	return !(port < PORT_MIN_BOUND || port > PORT_MAX_BOUND);
}

void CHttpUrl::FillProtocolMap()
{
	m_protocolMap.emplace("http", Protocol::HTTP);
	m_protocolMap.emplace("https", Protocol::HTTPS);
}

Protocol CHttpUrl::ParseProtocol(const string& protocolStr)
{
	string protocolToLowCase;
	transform(protocolStr.begin(), protocolStr.end(), back_inserter(protocolToLowCase), tolower);

	auto it = m_protocolMap.find(protocolToLowCase);
	if (it != m_protocolMap.end())
	{
		return it->second;
	}

	throw CUrlParsingError("Invalid protocol\n");
}

string CHttpUrl::ParseDomain(string const& domain)
{
	if (domain == "")
	{
		throw CUrlParsingError("Invalid domain\n");
	}
	return domain;
}

string CHttpUrl::GetURL() const
{
	return m_url;
}

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

string CHttpUrl::GetDocument() const
{
	return m_document;
}

string CHttpUrl::GetProtocolTitle() const
{
	for (auto& it : m_protocolMap)
	{
		if (it.second == m_protocol)
			return it.first;
	}
	throw CUrlParsingError("Invalid protocol\n");
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
