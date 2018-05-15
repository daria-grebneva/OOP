#pragma once
#include "stdafx.h"
#include "CUrlParsingError.h"

const int PORT_MIN_BOUND = 1;
const int PORT_MAX_BOUND = 65535;

enum Protocol
{
	HTTP = 80,
	HTTPS = 443,
};

class CHttpUrl

{

public:
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
	std::string GetProtocolTitle() const;

private:
	Protocol ParseProtocol(std::string const& protocol);
	std::string ParseDomain(std::string const& domain);
	unsigned short ParsePort(std::string const& url);
	std::string ParseDocument(std::string const& url);
	bool CheckPortInRange(unsigned short port);
	void FillProtocolMap();

	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
	std::map<std::string, Protocol> m_protocolMap;
};
