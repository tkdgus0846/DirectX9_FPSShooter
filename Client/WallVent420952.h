#pragma once
#include "WallTile.h"
class WallVent420952
	: public CWallTile
{
public:
	WallVent420952(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallVent420952();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallVent420952"; }

private:
	virtual HRESULT Add_Component() override;
};