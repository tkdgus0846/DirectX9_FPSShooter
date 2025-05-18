#pragma once
#include "WallTile.h"
class WallShortDoor
	: public CWallTile
{
public:
	WallShortDoor(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallShortDoor();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallShortDoor"; }

private:
	virtual HRESULT Add_Component() override;
};

