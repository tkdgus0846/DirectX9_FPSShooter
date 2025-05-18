#pragma once
#include "FloorTile.h"

class FloorVent421222
	: public CFloorTile
{
public:
	FloorVent421222(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorVent421222();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorVent421222"; }

private:
	virtual HRESULT Add_Component() override;
};