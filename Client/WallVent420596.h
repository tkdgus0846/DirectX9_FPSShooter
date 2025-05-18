#pragma once
#include "WallTile.h"
class WallVent420596
	: public CWallTile
{
public:
	WallVent420596(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallVent420596();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallVent420596"; }

private:
	virtual HRESULT Add_Component() override;
};
