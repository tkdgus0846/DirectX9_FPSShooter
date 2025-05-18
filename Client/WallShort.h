#pragma once
#include "WallTile.h"
class WallShort
	: public CWallTile
{
public:
	WallShort(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallShort();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallShort"; }

private:
	virtual HRESULT Add_Component() override;
};
