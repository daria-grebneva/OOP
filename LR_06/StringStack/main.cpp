#include "stdafx.h"
#include "CStringStack.h"

int main()
{
	try
	{
		CStringStack stringStack;
		stringStack.Push("string");
		stringStack.Pop();
		std::cout << stringStack.IsEmpty();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}
