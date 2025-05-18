#pragma once
#include "FloorTile.h"
class FloorLarge421874 :
	public CFloorTile
{
public:
	FloorLarge421874(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorLarge421874();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorLarge421874"; }

private:
	virtual HRESULT Add_Component() override;
};

