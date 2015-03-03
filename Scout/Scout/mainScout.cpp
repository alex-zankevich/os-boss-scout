#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;
HANDLE hInEvent[2];
HANDLE hMutex;
CHAR lpDashEventName[] = "DashEventName";
CHAR lpDotventName[] = "DotEventName";
CHAR lpMutex[] = "Mutex";
int main()
{
	char c;
	hInEvent[0] = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpDashEventName);
	if (hInEvent[0] == NULL)
	{
		cout << "Open event failed." << endl;
		cout << "Input any char to exit." << endl;
		cin >> c;
		return GetLastError();
	}
	hInEvent[1] = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpDotventName);
	if (hInEvent[1] == NULL)
	{
		cout << "Open event failed." << endl;
		cout << "Input any char to exit." << endl;
		cin >> c;
		return GetLastError();
	}
	hMutex = OpenMutex(SYNCHRONIZE, FALSE, lpMutex);
	if (hMutex == NULL)
	{
		cout << "Open mutex failed." << endl;
		cout << "Press any key to exit." << endl;
		cin.get();
		return GetLastError();
	}		
	c = _getch();
	WaitForSingleObject(hMutex, INFINITE);
	while (c == '-' || c == '.')
	{
		if (c == '-')
			SetEvent(hInEvent[0]);
		else
			if (c == '.')
				SetEvent(hInEvent[1]);
		c = _getch();
	}
	ReleaseMutex(hMutex);
	return 0;
}