#pragma once
#include "FloorTile.h"
class FloorSmall421575 :
	public CFloorTile
{
public:
	FloorSmall421575(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorSmall421575();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorSmall421575"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

