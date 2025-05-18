#pragma once
#include "WallTile.h"

class ShortWall 
	: public CWallTile
{
public:
	ShortWall(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ShortWall();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShortWall"; }

private:
	virtual HRESULT Add_Component() override;
};

