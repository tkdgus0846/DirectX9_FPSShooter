#pragma once
#include "FloorTile.h"
class FloorLarge421204 :
	public CFloorTile
{
public:
	FloorLarge421204(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorLarge421204();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorLarge421204"; }

private:
	virtual HRESULT Add_Component() override;
};

