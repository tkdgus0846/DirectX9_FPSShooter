#pragma once
#include "WallTile.h"
class WallLongDoor
	: public CWallTile
{
public:
	WallLongDoor(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallLongDoor();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallLongDoor"; }

private:
	virtual HRESULT Add_Component() override;
};

