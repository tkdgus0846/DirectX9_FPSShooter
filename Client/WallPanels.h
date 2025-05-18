#pragma once
#include "WallTile.h"
class WallPanels
	: public CWallTile
{
public:
	WallPanels(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels"; }

private:
	virtual HRESULT Add_Component() override;
};

