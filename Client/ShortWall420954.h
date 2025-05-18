#pragma once
#include "WallTile.h"

class ShortWall420954
	: public CWallTile
{
public:
	ShortWall420954(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ShortWall420954();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShortWall420954"; }

private:
	virtual HRESULT Add_Component() override;
};

