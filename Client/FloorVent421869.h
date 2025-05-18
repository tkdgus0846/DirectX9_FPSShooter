#pragma once
#include "FloorTile.h"

class FloorVent421869
	: public CFloorTile
{
public:
	FloorVent421869(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorVent421869();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorVent421869"; }

private:
	virtual HRESULT Add_Component() override;
};

