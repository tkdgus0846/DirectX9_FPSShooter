#pragma once
#include "WallTile.h"
class WallSpecial421565
	: public CWallTile
{
public:
	WallSpecial421565(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallSpecial421565();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallSpecial421565"; }

private:
	virtual HRESULT Add_Component() override;
};

