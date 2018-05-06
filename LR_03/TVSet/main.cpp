#include "stdafx.h"
#include "CTVSet.h"
#include "RemoteControl.h"

using namespace std;

int main()
{
	CTVSet tv;
	CRemoteControl remoteControl(tv, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!remoteControl.ProcessCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
}
