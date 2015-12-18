#include "GameHeader.h"
#include "RenderEngine\DXUtils.h"
#include "GSystemEngine.h"


bool WinCreate(HWND hwnd)
{
	GSystemEngine::getInstance()->InitEngine();
	GSystemEngine::getInstance()->Init();
	dxInit(hwnd);

	
	


	return true;
}
