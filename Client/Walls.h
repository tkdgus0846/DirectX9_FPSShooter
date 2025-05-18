#pragma once
#include "WallTile.h"
class Walls
	: public CWallTile
{
public:
	Walls(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~Walls();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Walls"; }

private:
	virtual HRESULT Add_Component() override;
};

