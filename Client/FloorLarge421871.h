#pragma once
#include "FloorTile.h"
class FloorLarge421871 :
	public CFloorTile
{
public:
	FloorLarge421871(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorLarge421871();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorLarge421871"; }

private:
	virtual HRESULT Add_Component() override;
};

