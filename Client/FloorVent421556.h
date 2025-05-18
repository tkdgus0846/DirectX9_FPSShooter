#pragma once
#include "FloorTile.h"

class FloorVent421556
	: public CFloorTile
{
public:
	FloorVent421556(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorVent421556();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorVent421556"; }

private:
	virtual HRESULT Add_Component() override;
};

