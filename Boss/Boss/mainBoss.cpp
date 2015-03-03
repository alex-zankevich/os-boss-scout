#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hInEvent[2];
HANDLE hMutex;
CHAR lpDashEventName[] = "DashEventName";
CHAR lpDotventName[] = "DotEventName";
CHAR lpMutex[] = "Mutex";

int main()
{
	DWORD dwWaitResult;
	char szAppName[] = "C:\\Users\\user\\Documents\\Visual Studio 2013\\Projects\\Scout\\Debug\\Scout.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	int nCount = 0;
	cout << "Enter number of processes : ";
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

	hMutex = CreateMutex(NULL, FALSE, lpMutex);
	if (hMutex == NULL)
	{
		cout << "Create mutex failed." << endl;
		cout << "Press any key to exit." << endl;
		cin.get();
		return GetLastError();
	}

	do
	{
		dwWaitResult = WaitForMultipleObjects(2, hInEvent, FALSE, INFINITE);
		if (dwWaitResult == WAIT_OBJECT_0)
			cout << "-";
		else
			if (dwWaitResult == (WAIT_OBJECT_0 + 1))
				cout << ".";
		
	} while (true);
	
	return 0;
}