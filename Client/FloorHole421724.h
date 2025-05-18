#pragma once
#include "FloorTile.h"
class FloorHole421724 :
	public CFloorTile
{
public:
	FloorHole421724(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorHole421724();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorHole421724"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

