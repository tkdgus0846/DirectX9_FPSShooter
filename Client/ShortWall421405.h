#pragma once
#include "WallTile.h"
class ShortWall421405
	: public CWallTile
{
public:
	ShortWall421405(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ShortWall421405();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShortWall421405"; }

private:
	virtual HRESULT Add_Component() override;
};

