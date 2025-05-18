#pragma once
#include "WallTile.h"
class WallSpecial
	: public CWallTile
{
public:
	WallSpecial(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallSpecial();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallSpecial"; }

private:
	virtual HRESULT Add_Component() override;
};
