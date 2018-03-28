#include "stdafx.h"

#include "URL_parser.h"

using namespace std;

Protocol ParseProtocol(const string& protocolStr)
{
	string protocolToLowCase;
	transform(protocolStr.begin(), protocolStr.end(), back_inserter(protocolToLowCase), tolower);
	if (protocolToLowCase == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocolToLowCase == "https")
	{
		return Protocol::HTTPS;
	}
	else if (protocolToLowCase == "ftp")
	{
		return Protocol::FTP;
	}
	return Protocol::InvalidProtocol;
}

void ShowInstruction()
{
	cout << "Usage: URL Parser.exe <URL-string>" << endl;
	cout << "Port must be in range " << PORT_MIN_BOUND << " " << PORT_MAX_BOUND << endl;
}

void UseDefaultPort(const Protocol& protocol, int& port)
{
	if (port == static_cast<int>(Protocol::HTTP) || port == static_cast<int>(Protocol::HTTPS)
		|| port == static_cast<int>(Protocol::FTP))
	{
		if (protocol == Protocol::HTTP)
		{
			port = 80;
		}
		else if (protocol == Protocol::HTTPS)
		{
			port = 443;
		}
		else if (protocol == Protocol::FTP)
		{
			port = 21;
		}
	}
}

bool CheckPortRange(int port)
{
	if (port < PORT_MIN_BOUND || port > PORT_MAX_BOUND)
	{
		ShowInstruction();
		return false;
	}
	return true;
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	smatch result;
	regex reg(R"(^(\w+):\/\/([A-Za-z0-9-.]+)(?::([0-9]+))?(?:\/(\S*))?$)", regex::icase);
	bool mapped = regex_search(url, result, reg);
	if (!mapped)
	{
		return false;
	}

	protocol = ParseProtocol(result[1].str());
	if (protocol == Protocol::InvalidProtocol)
	{
		return false;
	}

	host = result[2].str();
	port = result[3].matched ? stoi(result[3].str()) : static_cast<int>(protocol);

	UseDefaultPort(protocol, port);

	if (!CheckPortRange(port))
	{
		return false;
	}
	document = result[4].str();

	return true;
}

void PrintInfoOfURLs(const string& url, int port, const string& host, const string& document)
{
	cout << url << endl
		 << "HOST: " << host << endl
		 << "PORT: " << port << endl
		 << "DOC: " << document << endl;
}

void ParseURLs()
{
	string url;
	while (getline(cin, url))
	{
		if (url.empty())
		{
			break;
		}

		int port;
		string host;
		string document;
		Protocol protocol;
		if (!ParseURL(url, protocol, port, host, document))
		{
			cout << "URL parsing failed" << endl;
			ShowInstruction();
			continue;
		}

		PrintInfoOfURLs(url, port, host, document);
	}
}
