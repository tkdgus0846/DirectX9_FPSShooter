#pragma once
#include "ImWindow.h"

class ImImage;
class CFactory;

class CImPickBox :
	public CImWindow
{
protected:
	CImPickBox(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImPickBox();

public:
	virtual HRESULT Ready_ImWindow() override;
	virtual _int Update(float fTimeDelta) override;

	static CImPickBox * Create(LPDIRECT3DDEVICE9 pGraphicDev, string name, CFactory * pFactory);

	void Set_Name(string name) 
	{
		m_name = name.c_str();
	}

	void Set_Factory(CFactory* pFactory)
	{
		m_pFactory = pFactory;
	}
	string Get_CurItem() { return m_Item; }

protected:
	virtual void Free() override;

protected:
	string m_name;
	string m_Item = "a";
	ImImage* m_pImage;
	CFactory* m_pFactory;
};