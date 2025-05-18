#pragma once
#include "WallTile.h"
class WallPanels421417
	: public CWallTile
{
public:
	WallPanels421417(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels421417();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels421417"; }

private:
	virtual HRESULT Add_Component() override;
};

