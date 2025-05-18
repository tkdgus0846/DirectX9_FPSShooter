#pragma once
#include "WallTile.h"
class WallPanels420377
	: public CWallTile
{
public:
	WallPanels420377(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~WallPanels420377();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WallPanels420377"; }

private:
	virtual HRESULT Add_Component() override;
};

