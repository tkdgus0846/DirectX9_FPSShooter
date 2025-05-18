#pragma once
#include "FloorTile.h"

class FloorVent421406
	: public CFloorTile
{
public:
	FloorVent421406(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorVent421406();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorVent421406"; }

private:
	virtual HRESULT Add_Component() override;
};

