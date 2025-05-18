#pragma once
#include "WallTile.h"
class ShortWall421217
	: public CWallTile
{
public:
	ShortWall421217(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ShortWall421217();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShortWall421217"; }

private:
	virtual HRESULT Add_Component() override;
};

