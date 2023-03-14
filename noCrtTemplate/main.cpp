#include "application.h"
#include "tests.h"

#include <Windows.h>

void __stdcall _mainCRTStartup()
{
	TestRoutine();

	WinMain(GetModuleHandle(0), NULL, NULL, SW_SHOWDEFAULT);
	ExitProcess(0);
}