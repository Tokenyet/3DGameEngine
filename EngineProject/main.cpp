#include <Windows.h>
#include "GameLooper.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	GameLooper::Loop();
	return 0;
}
