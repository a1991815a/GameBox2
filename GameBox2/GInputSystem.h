#ifndef __GINPUTSYSTEM__
#define __GINPUTSYSTEM__
#include "GSystem.h"
#include <dinput.h>

#define GINPUT_KEYSIZE 256

class GInputSystem: 
	public GSystem, 
	public SingleInstance<GInputSystem>,
	public GWinProcessor
{
public:
	GInputSystem();

	//获得键盘和鼠标控制权
	bool Acquire();
	//解除键盘和鼠标控制权
	bool UnAcquire();
	//准备数据 (获取当前键盘鼠标数据)
	void ReadyData();
	



	virtual bool Init() override;
	virtual void Destroy() override;

	bool InputProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	//交换鼠标缓冲指针
	void SwapBuf();
private:
	IDirectInput8*				m_pDInput;
	IDirectInputDevice8*		m_pKeyboardDevice;
	IDirectInputDevice8*		m_pMouseDevice;
	char*						m_pPreKeyBuf;				//上一次鼠标按键状态
	char*						m_pCurKeyBuf;				//本次鼠标按键状态
	DIMOUSESTATE2*				m_pPreMoustState;				//上一次鼠标状态
	DIMOUSESTATE2*				m_pCurMouseState;			//本次鼠标状态
};
#endif