#pragma once
#include "WallTile.h"
class WallPipes420605
	: public CWallTile
{
public:
	WallPipes420605(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPipes420605();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPipes420605"; }

private:
	virtual HRESULT Add_Component() override;
};

