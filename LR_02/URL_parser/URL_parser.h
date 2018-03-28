#pragma once

using namespace std;

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	InvalidProtocol
};

const int PORT_MIN_BOUND = 1;
const int PORT_MAX_BOUND = 65535;

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document);
void ParseURLs();
void PrintURLInfo(const string& url, int port, const string& host, const string& document);
