#pragma once
#include "WallTile.h"
class WallPanels421568
	: public CWallTile
{
public:
	WallPanels421568(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels421568();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels421568"; }

private:
	virtual HRESULT Add_Component() override;
};

