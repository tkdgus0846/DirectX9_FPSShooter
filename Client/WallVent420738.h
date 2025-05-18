#pragma once
#include "WallTile.h"
class WallVent420738
	: public CWallTile
{
public:
	WallVent420738(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallVent420738();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallVent420738"; }

private:
	virtual HRESULT Add_Component() override;
};