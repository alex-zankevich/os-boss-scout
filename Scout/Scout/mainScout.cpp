// Пример синхронизации потоков в разных процессах
// с использованием именованного события
#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;
HANDLE hInEvent[2];
CHAR lpDashEventName[] = "DashEventName";
CHAR lpDotventName[] = "DotEventName";
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
	c = _getche();
	while (c == '-' || c == '.')
	{
		if (c == '-')
			SetEvent(hInEvent[0]);
		else
			if (c == '.')
				SetEvent(hInEvent[1]);
		c = _getche();
	}
	return 0;
}