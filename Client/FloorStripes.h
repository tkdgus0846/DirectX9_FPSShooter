#pragma once
#include "FloorTile.h"

class FloorStripes
	: public CFloorTile
{
public:
	FloorStripes(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorStripes();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorStripes"; }

private:
	virtual HRESULT Add_Component() override;
};

