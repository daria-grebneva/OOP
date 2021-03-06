#include "stdafx.h"
#include "CShapeMaker.h"
#include <fstream>

int main()
{
	try
	{
		const std::string inputFileName = "house.txt";
		std::fstream fin(inputFileName);

		if (!fin.is_open())
		{
			throw std::exception("Can not open file");
		}

		CShapeMaker shape(fin);

		while (!fin.eof() && !fin.fail())
		{
			shape.ExecuteCommand();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	return 0;
}
