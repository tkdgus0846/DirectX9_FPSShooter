#pragma once
#include "WallTile.h"
class WallVent
	: public CWallTile
{
public:
	WallVent(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallVent();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallVent"; }

private:
	virtual HRESULT Add_Component() override;
};

