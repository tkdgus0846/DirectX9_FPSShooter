#pragma once
#include "WallTile.h"
class WallPanels420744
	: public CWallTile
{
public:
	WallPanels420744(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels420744();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels420744"; }

private:
	virtual HRESULT Add_Component() override;
};

