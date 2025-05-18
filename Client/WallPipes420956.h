#pragma once
#include "WallTile.h"
class WallPipes420956
	: public CWallTile
{
public:
	WallPipes420956(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPipes420956();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPipes420956"; }

private:
	virtual HRESULT Add_Component() override;
};

