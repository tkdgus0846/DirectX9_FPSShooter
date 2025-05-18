#pragma once

#include "Base.h"
#include "Include.h"

BEGIN(Engine)

class  CDInputMgr : public CBase
{
	DECLARE_SINGLETON(CDInputMgr)

private:
	explicit CDInputMgr();
	virtual ~CDInputMgr();

public:
	_byte		Get_DIKeyState(_ubyte ubyKeyID) 
	{
		return m_byKeyState[ubyKeyID];
	}
	_byte		Get_DIMouseState(MOUSEKEYSTATE eMouseID)
	{
		return m_tMouseState.rgbButtons[eMouseID];
	}

	_long		Get_DIMouseMove(MOUSEMOVESTATE eMouseMoveID)
	{
		return *(((_long*)&m_tMouseState) + eMouseMoveID);
	}

public:
	HRESULT	Ready_DInput(HINSTANCE hInst, HWND hWnd);
	void	Update_DInput(void);

	bool	Key_Pressing(_ubyte ubyKey);
	bool	Key_Down(_ubyte ubyKey);
	bool	Key_Up(_ubyte ubyKey);

	bool	Mouse_Down(MOUSEKEYSTATE eMouseID);
	bool	Mouse_Pressing(MOUSEKEYSTATE eMouseID);
	bool	Mouse_Up(MOUSEKEYSTATE eMouseID);

private:
	LPDIRECTINPUT8			m_pInputSDK;

	LPDIRECTINPUTDEVICE8	m_pKeyBoard;
	LPDIRECTINPUTDEVICE8	m_pMouse;

private:
	_byte					m_byKeyState[MAX_DIK];
	_byte					m_byPreKeyState[MAX_DIK];
	DIMOUSESTATE			m_tMouseState;
	DIMOUSESTATE			m_tPreMouseState;

public:
	virtual void		Free(void);

};

END