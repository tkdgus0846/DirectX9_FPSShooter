#pragma once
#include "WallTile.h"
class WallSpecial420958
	: public CWallTile
{
public:
	WallSpecial420958(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallSpecial420958();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallSpecial420958"; }

private:
	virtual HRESULT Add_Component() override;
};

