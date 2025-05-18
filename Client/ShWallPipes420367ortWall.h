#pragma once
#include "WallTile.h"
class ShWallPipes420367ortWall
	: public CWallTile
{
public:
	ShWallPipes420367ortWall(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ShWallPipes420367ortWall();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShWallPipes420367ortWall"; }

private:
	virtual HRESULT Add_Component() override;
};

