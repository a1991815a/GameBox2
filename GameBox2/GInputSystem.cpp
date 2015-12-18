#include "GInputSystem.h"
#include "GApplication.h"

#define FAILED_THORW(cond, msg) \
while(!(cond)) throw std::runtime_error(msg)

GInputSystem::GInputSystem()
	:GSystem(10, "GInputSystem(输入系统)"),
	m_pDInput(nullptr), m_pKeyboardDevice(nullptr), m_pMouseDevice(nullptr)
{

}

bool GInputSystem::Acquire()
{
	if (!m_pMouseDevice->Acquire())
		return false;
	if (!m_pKeyboardDevice->Acquire())
		return false;
	return true;
}

bool GInputSystem::UnAcquire()
{
	if (!m_pMouseDevice->Unacquire())
		return false;
	if (!m_pKeyboardDevice->Unacquire())
		return false;
	return true;
}

bool GInputSystem::Init()
{
	//DInput8接口创建
	HRESULT result = S_OK;
	result = DirectInput8Create(
		GetModuleHandleA(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8A,
		(void**)&m_pDInput,
		nullptr
		);
	FAILED_THORW(result, "DirectInput8Create");
	
	//键盘设备创建
	{
		result = m_pDInput->CreateDevice(
			GUID_SysKeyboard,
			&m_pKeyboardDevice,
			nullptr
			);
		FAILED_THORW(result, "CreateDevice: Keyboard");
		result = m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		FAILED_THORW(result, "SetDataFormat: Keyboard");
		result = m_pKeyboardDevice->SetCooperativeLevel(
			dxGetApp()->getWindow(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
		FAILED_THORW(result, "SetCooperativeLevel: Keyboard");
	};

	//鼠标设备接口创建
	{
		result = m_pDInput->CreateDevice(
			GUID_SysMouse,
			&m_pMouseDevice,
			nullptr
			);
		FAILED_THORW(result, "CreateDevice: Mouse");
		result = m_pMouseDevice->SetDataFormat(&c_dfDIMouse2);
		FAILED_THORW(result, "SetDataFormat: Mouse");
		result = m_pMouseDevice->SetCooperativeLevel(
			dxGetApp()->getWindow(),
			DISCL_FOREGROUND | DISCL_EXCLUSIVE
			);
		FAILED_THORW(result, "SetCooperativeLevel: Mouse");
	};

	//缓冲区创建
	{
		m_pPreKeyBuf = new char[GINPUT_KEYSIZE];
		m_pCurKeyBuf = new char[GINPUT_KEYSIZE];
		m_pPreMoustState = new DIMOUSESTATE2();
		m_pCurMouseState = new DIMOUSESTATE2();
		memset(m_pPreKeyBuf, 0, GINPUT_KEYSIZE);
		memset(m_pCurKeyBuf, 0, GINPUT_KEYSIZE);
		memset(m_pPreMoustState, 0, sizeof(DIMOUSESTATE2));
		memset(m_pCurMouseState, 0, sizeof(DIMOUSESTATE2));
	}

	dxGetApp()->RegisterProcess((GWinProcessor*)this, GPROC_CALLBACK(GInputSystem::InputProcess));
	Acquire();


	return true;
}

void GInputSystem::ReadyData()
{
	SwapBuf();
	m_pKeyboardDevice->GetDeviceState(GINPUT_KEYSIZE, (void*)&m_pCurKeyBuf);
	m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), (void*)&m_pCurMouseState);
}

void GInputSystem::Destroy()
{
	if (m_pKeyboardDevice)
		m_pKeyboardDevice->Unacquire();
	if (m_pMouseDevice)
		m_pMouseDevice->Unacquire();
	SAFE_RELEASE_COM(m_pMouseDevice);
	SAFE_RELEASE_COM(m_pKeyboardDevice);
	SAFE_RELEASE_COM(m_pDInput);

	SAFE_DELETE_ARRAY(m_pPreKeyBuf);
	SAFE_DELETE_ARRAY(m_pCurKeyBuf);
	SAFE_DELETE(m_pPreMoustState);
	SAFE_DELETE(m_pCurMouseState);
}

bool GInputSystem::InputProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:
		switch (wParam)
		{
		case WA_ACTIVE:
			Acquire();
			break;
		case WA_INACTIVE:
			UnAcquire();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;
}

void GInputSystem::SwapBuf()
{
	char* tmp_buf = m_pPreKeyBuf;
	m_pPreKeyBuf = m_pCurKeyBuf;
	m_pCurKeyBuf = tmp_buf;
	DIMOUSESTATE2* tmp_mbuf = m_pPreMoustState;
	m_pPreMoustState = m_pCurMouseState;
	m_pCurMouseState = tmp_mbuf;
}
