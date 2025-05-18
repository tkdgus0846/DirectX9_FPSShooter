#pragma once
#include "FloorTile.h"
class FloorSmall421201 :
	public CFloorTile
{
public:
	FloorSmall421201(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorSmall421201();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorSmall421201"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

