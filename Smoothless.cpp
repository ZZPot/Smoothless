#include <windows.h>
#include <tchar.h>


BOOL setFontSmoothing(BOOL newState)
{
	return SystemParametersInfo(SPI_SETFONTSMOOTHING, newState, NULL, SPIF_SENDCHANGE);
}

BOOL getFontSmoothing()
{
	BOOL res;
	SystemParametersInfo(SPI_GETFONTSMOOTHING, NULL, &res, NULL);
	return res;
}

VOID startProcess(PTSTR cmd)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int WINAPI _tWinMain(	_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ PTSTR cmdLine,
						_In_ int nShowCmd)
{
	if (_tcslen(cmdLine) == 0)
		return 1;
	BOOL prevState = getFontSmoothing();
	BOOL res = setFontSmoothing(FALSE);
	startProcess(cmdLine);
	Sleep(1000);
	res = setFontSmoothing(prevState);
	return 0;
}