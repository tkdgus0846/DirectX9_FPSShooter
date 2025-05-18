#pragma once
#include "WallTile.h"
class WallVent421863
	: public CWallTile
{
public:
	WallVent421863(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallVent421863();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallVent421863"; }

private:
	virtual HRESULT Add_Component() override;
};