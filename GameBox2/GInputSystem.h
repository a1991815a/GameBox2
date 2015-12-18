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

	//��ü��̺�������Ȩ
	bool Acquire();
	//������̺�������Ȩ
	bool UnAcquire();
	//׼������ (��ȡ��ǰ�����������)
	void ReadyData();
	



	virtual bool Init() override;
	virtual void Destroy() override;

	bool InputProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	//������껺��ָ��
	void SwapBuf();
private:
	IDirectInput8*				m_pDInput;
	IDirectInputDevice8*		m_pKeyboardDevice;
	IDirectInputDevice8*		m_pMouseDevice;
	char*						m_pPreKeyBuf;				//��һ����갴��״̬
	char*						m_pCurKeyBuf;				//������갴��״̬
	DIMOUSESTATE2*				m_pPreMoustState;				//��һ�����״̬
	DIMOUSESTATE2*				m_pCurMouseState;			//�������״̬
};
#endif