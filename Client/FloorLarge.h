#pragma once
#include "FloorTile.h"
class FloorLarge :
	public CFloorTile
{
public:
	FloorLarge(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorLarge();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorLarge"; }

private:
	virtual HRESULT Add_Component() override;
};

