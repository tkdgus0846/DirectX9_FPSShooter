#pragma once
#include "ImWindow.h"

class CImTest :
	public CImWindow
{
private:
	explicit CImTest(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImTest();

public:
	virtual HRESULT Ready_ImWindow() override;
	virtual _int	Update(float fTimeDelta) override;
	
	static CImTest* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	// ���� ��� + ���ϸ� ���
	//string GetFilePathName() { return m_strFilePathName; }
	// ���� ��θ� ���
	//string GetFilePath() { return m_strFilePath; }
	// ���� �̸��� ���
	//string GetFileName() { return m_strFileName; }

private:
	void FileDialog();

	void Save();
	void Load();

private:
	_bool			m_bOpenButton = false;
	_bool			m_bIsSave = false;
	wstring			m_strFilePathName;
	wstring			m_strFilePath;
	wstring			m_strFileName;

private:
	virtual void Free(void) override;
};


