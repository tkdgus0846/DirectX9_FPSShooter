#pragma once
#include "FloorTile.h"
class FloorHole421573 :
	public CFloorTile
{
public:
	FloorHole421573(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorHole421573();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorHole421573"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

