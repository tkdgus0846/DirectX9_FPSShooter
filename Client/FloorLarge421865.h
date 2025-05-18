#pragma once
#include "FloorTile.h"
class FloorLarge421865 :
	public CFloorTile
{
public:
	FloorLarge421865(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorLarge421865();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorLarge421865"; }

private:
	virtual HRESULT Add_Component() override;
};

