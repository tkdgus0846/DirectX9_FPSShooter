#pragma once
#include "FloorTile.h"
class CBloodTile :
	public CFloorTile
{
private:
	CBloodTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBloodTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CTile* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

