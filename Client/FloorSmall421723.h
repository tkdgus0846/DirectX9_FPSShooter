#pragma once
#include "FloorTile.h"
class FloorSmall421723 :
	public CFloorTile
{
public:
	FloorSmall421723(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorSmall421723();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorSmall421723"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

