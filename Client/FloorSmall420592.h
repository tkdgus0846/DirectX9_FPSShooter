#pragma once
#include "FloorTile.h"
class FloorSmall420592 :
	public CFloorTile
{
public:
	FloorSmall420592(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorSmall420592();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorSmall420592"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

