#pragma once
#include "WallTile.h"
class WallPanels420948
	: public CWallTile
{
public:
	WallPanels420948(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels420948();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels420948"; }

private:
	virtual HRESULT Add_Component() override;
};

