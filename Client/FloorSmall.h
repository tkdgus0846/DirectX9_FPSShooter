#pragma once
#include "FloorTile.h"
class FloorSmall :
	public CFloorTile
{
public:
	FloorSmall(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorSmall();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorSmall"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

