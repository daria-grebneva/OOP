#include "stdafx.h"

#include "URL_parser.h"

using namespace std;

void FillProtocolMap(std::map<std::string, Protocol>& protocolValue)
{
	protocolValue.emplace("http", Protocol::HTTP);
	protocolValue.emplace("https", Protocol::HTTPS);
	protocolValue.emplace("ftp", Protocol::FTP);
}

Protocol ParseProtocol(const string& protocolStr)
{
	std::map<std::string, Protocol> protocolValue;
	FillProtocolMap(protocolValue);
	string protocolToLowCase;
	transform(protocolStr.begin(), protocolStr.end(), back_inserter(protocolToLowCase), tolower);

	auto it = protocolValue.find(protocolToLowCase);
	if (it != protocolValue.end())
	{
		return it->second;
	}

	return Protocol::InvalidProtocol;
}

void ShowUsage()
{
	cout << "Usage: URL Parser.exe <URL-string>" << endl;
	cout << "Port must be in range " << PORT_MIN_BOUND << " " << PORT_MAX_BOUND << endl;
}

void UseDefaultPort(const Protocol& protocol, int& port)
{
	if (port == static_cast<int>(Protocol::HTTP)
		|| port == static_cast<int>(Protocol::HTTPS)
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

bool CheckPortInRange(int port)
{
	if (port < PORT_MIN_BOUND || port > PORT_MAX_BOUND)
	{
		ShowUsage();
		return false;
	}
	return true;
}

bool ParseURLImpl(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	smatch result;
	regex reg(R"(^(\w+):\/\/([^\s:\/]+)(?::(\d+))?(?:\/(\S*))?$)", regex::icase);
	bool mapped = regex_search(url, result, reg);

	if (!mapped)
	{
		return false;
	}

	protocol = ParseProtocol(result[1]);
	if (protocol == Protocol::InvalidProtocol)
	{
		return false;
	}

	host = result[2];

	port = result[3].matched ? stoi(result[3]) : static_cast<int>(protocol);
	const string str = result[3];
	if (str.empty())
	{
		UseDefaultPort(protocol, port);
	}
	else if (!CheckPortInRange(port))
	{
		return false;
	}
	document = result[4];

	return true;
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	try
	{
		return ParseURLImpl(url, protocol, port, host, document);
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return false;
	}
}

void PrintURLInfo(const string& url, int port, const string& host, const string& document)
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
			ShowUsage();
			continue;
		}

		PrintURLInfo(url, port, host, document);
	}
}
