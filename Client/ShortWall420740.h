#pragma once
#include "WallTile.h"

class ShortWall420740 
	: public CWallTile
{
public:
	ShortWall420740(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ShortWall420740();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShortWall420740"; }

private:
	virtual HRESULT Add_Component() override;
};

