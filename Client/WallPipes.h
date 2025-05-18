#pragma once
#include "WallTile.h"
class WallPipes
	: public CWallTile
{
public:
	WallPipes(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPipes();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPipes"; }

private:
	virtual HRESULT Add_Component() override;
};
