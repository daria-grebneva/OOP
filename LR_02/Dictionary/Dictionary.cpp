#include "stdafx.h"

#include "Dictionary.h"

using namespace std;

const unsigned ARG_COUNT = 2;

bool IsValidArgumentsCount(int argc)
{
	return (argc == ARG_COUNT);
}

bool IsFileExist(std::string& fileName)
{
	bool isExist = false;
	std::ifstream fin(fileName.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}


