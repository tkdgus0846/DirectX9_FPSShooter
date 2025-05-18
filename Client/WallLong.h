#pragma once
#include "WallTile.h"
class WallLong
	: public CWallTile
{
public:
	WallLong(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallLong();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallLong"; }

private:
	virtual HRESULT Add_Component() override;
};

