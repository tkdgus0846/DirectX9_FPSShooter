#pragma once
#include "WallTile.h"
class WallPanels420595
	: public CWallTile
{
public:
	WallPanels420595(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels420595();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels420595"; }

private:
	virtual HRESULT Add_Component() override;
};

