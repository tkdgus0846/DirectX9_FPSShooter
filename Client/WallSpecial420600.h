#pragma once
#include "WallTile.h"
class WallSpecial420600
	: public CWallTile
{
public:
	WallSpecial420600(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallSpecial420600();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallSpecial420600"; }

private:
	virtual HRESULT Add_Component() override;
};

