#pragma once
#include "FloorTile.h"

class FloorVent420959
	: public CFloorTile
{
public:
	FloorVent420959(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorVent420959();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorVent420959"; }

private:
	virtual HRESULT Add_Component() override;

};