#pragma once
#include "WallTile.h"
class WallSpecial420730
	: public CWallTile
{
public:
	WallSpecial420730(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallSpecial420730();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallSpecial420730"; }

private:
	virtual HRESULT Add_Component() override;
};

