#pragma once
#include "FloorTile.h"
class FloorLarge421721 :
	public CFloorTile
{
public:
	FloorLarge421721(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorLarge421721();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorLarge421721"; }

private:
	virtual HRESULT Add_Component() override;
};

