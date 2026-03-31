#include "DxLib.h"
#include "System/SystemMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SystemMain system;
	if (system.initialize()) {

		system.main();
	}
	system.finalize();
}