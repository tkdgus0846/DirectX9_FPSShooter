#pragma once
#include "WallTile.h"
class WallPanels421219
	: public CWallTile
{
public:
	WallPanels421219(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels421219();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels421219"; }

private:
	virtual HRESULT Add_Component() override;
};

