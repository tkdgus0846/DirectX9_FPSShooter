#pragma once
#include "WallTile.h"
class WallPanels421731
	: public CWallTile
{
public:
	WallPanels421731(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels421731();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels421731"; }

private:
	virtual HRESULT Add_Component() override;
};
