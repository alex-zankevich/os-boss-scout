// Пример синхронизации потоков в разных процессах
// с использованием именованного события
#include <windows.h>
#include <iostream>
using namespace std;
HANDLE hInEvent[2];
CHAR lpDashEventName[] = "DashEventName";
CHAR lpDotventName[] = "DotEventName";
int main()
{
	DWORD dwWaitResult;
	char szAppName[] = "C:\\Users\\user\\Documents\\Visual Studio 2013\\Projects\\Scout\\Debug\\Scout.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	int nCount = 0;
	if (!(cin >> nCount))
		return 1;

	hInEvent[0] = CreateEvent(NULL, FALSE, FALSE, lpDashEventName);
	if (hInEvent[0] == NULL)
		return GetLastError();
	hInEvent[1] = CreateEvent(NULL, FALSE, FALSE, lpDotventName);
	if (hInEvent[1] == NULL)
		return GetLastError();
	
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	for (int i = 0; i < nCount; i++)
	{
		if (!CreateProcess(szAppName, NULL, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
			return 0;
	}
	while (true)
	{
		dwWaitResult = WaitForMultipleObjects(2, hInEvent, FALSE, INFINITE);
		if (dwWaitResult == WAIT_OBJECT_0)
			cout << "-";
		else
			if (dwWaitResult == (WAIT_OBJECT_0 + 1))
				cout << ".";
	}
	return 0;
}