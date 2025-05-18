#pragma once
#include "WallTile.h"
class WallVent420375
	: public CWallTile
{
public:
	WallVent420375(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallVent420375();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallVent420375"; }

private:
	virtual HRESULT Add_Component() override;
};

