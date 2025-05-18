#pragma once
#include "WallTile.h"
class WallPipes420745
	: public CWallTile
{
public:
	WallPipes420745(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPipes420745();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPipes420745"; }

private:
	virtual HRESULT Add_Component() override;
};

