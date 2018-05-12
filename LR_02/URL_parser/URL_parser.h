#pragma once
#include <map>
enum Protocol
{
	HTTP,
	HTTPS,
	FTP,
	InvalidProtocol
};

const int PORT_MIN_BOUND = 1;
const int PORT_MAX_BOUND = 65535;

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
void ParseURLs();
void PrintURLInfo(const std::string& url, int port, const std::string& host, const std::string& document);
