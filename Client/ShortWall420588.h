#pragma once
#include "WallTile.h"
class ShortWall420588
	: public CWallTile
{
public:
	ShortWall420588(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ShortWall420588();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShortWall420588"; }

private:
	virtual HRESULT Add_Component() override;
};

