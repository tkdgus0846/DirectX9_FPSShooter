#pragma once
#include "FloorTile.h"
class FloorVent421725
	: public CFloorTile
{
public:
	FloorVent421725(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorVent421725();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorVent421725"; }

private:
	virtual HRESULT Add_Component() override;
};

