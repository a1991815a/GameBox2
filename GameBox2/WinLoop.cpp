#include "GameHeader.h"
#include "RenderEngine\DXUtils.h"
#include "GTimerSystem.h"
GTimer* timer = nullptr;

void WinLoop(){
	if (timer == nullptr)
		timer = new GTimer();

	_timerSystem->Refresh();


	LOG_I("��ʱ��: %f", timer->getElapse());

	dxBeginScene();

	dxEndScene();
};
