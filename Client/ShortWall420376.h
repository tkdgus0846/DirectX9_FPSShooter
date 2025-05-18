#pragma once
#include "WallTile.h"
class ShortWall420376 :
	public CWallTile
{
public:
	ShortWall420376(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ShortWall420376();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShortWall420376"; }

private:
	virtual HRESULT Add_Component() override;
};

