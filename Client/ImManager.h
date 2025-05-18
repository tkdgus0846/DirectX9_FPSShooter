#pragma once

#include "Include.h"
//#include "ImWindow.h"
BEGIN(Engine)

class CFloorTex;
class CTransform;
class CPickingSphere;

END

class CImManager
{
	DECLARE_SINGLETON(CImManager)

public:
	CImManager();
	~CImManager();

	HRESULT Ready_IMGUI(LPDIRECT3DDEVICE9 pGraphicDev);
	_int Update(_float fTimeDelta);
	void Render(LPDIRECT3DDEVICE9 pGraphicDev);
	void Release();
	class CImWindow* FindByTag(wstring tag);

public:
	void AddContainer(wstring key, CImWindow* pImWindow);

private:
	map<wstring, CImWindow*> m_mapImWindow;
};

#define IM_MGR  CImManager::GetInstance()
#define FIND_IM(tag) IM_MGR->FindByTag(tag)