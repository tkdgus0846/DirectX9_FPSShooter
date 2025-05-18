#pragma once

#include "ImWindow.h"


class CImMenuBar :
	public CImWindow
{
protected:
	explicit CImMenuBar(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImMenuBar();

public:
	virtual HRESULT Ready_ImWindow();
	virtual _int Update(float fTimeDelta);

	static CImMenuBar* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	void SaveFileDialog();
	void LoadFileDialog();

private:
	_bool			m_bSaveButton = false;
	_bool			m_bLoadButton = false;
	_bool			m_bIsSave = false;
	wstring			m_strFilePathName;
	wstring			m_strFilePath;
	wstring			m_strFileName;

protected:
	virtual void Free(void);
};