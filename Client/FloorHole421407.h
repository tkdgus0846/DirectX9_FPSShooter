#pragma once
#include "FloorTile.h"
class FloorHole421407 :
	public CFloorTile
{
public:
	FloorHole421407(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorHole421407();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorHole421407"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

