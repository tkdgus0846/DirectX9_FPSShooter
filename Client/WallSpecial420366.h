#pragma once
#include "WallTile.h"
class WallSpecial420366
	: public CWallTile
{
public:
	WallSpecial420366(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallSpecial420366();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallSpecial420366"; }

private:
	virtual HRESULT Add_Component() override;
};

