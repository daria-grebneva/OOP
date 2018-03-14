#include "Dictionary.h"

using namespace std;

int main(int argc, wchar_t * argv[])
{
	std::locale::global(std::locale("rus"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (!IsValidArgumentsCount(argc))
	{
		cout << "Wrong number of arguments" << endl;
		return 1;
	}



}
