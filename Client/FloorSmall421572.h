#pragma once
#include "FloorTile.h"
class FloorSmall421572 :
	public CFloorTile
{
public:
	FloorSmall421572(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorSmall421572();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorSmall421572"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

