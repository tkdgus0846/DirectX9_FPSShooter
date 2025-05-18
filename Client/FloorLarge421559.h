#pragma once
#include "FloorTile.h"
class FloorLarge421559 :
	public CFloorTile
{
public:
	FloorLarge421559(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorLarge421559();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorLarge421559"; }

private:
	virtual HRESULT Add_Component() override;
};

