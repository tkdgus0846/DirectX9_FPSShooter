#pragma once
#include "FloorTile.h"
class CSnowTile :
	public CFloorTile
{
private:
	CSnowTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSnowTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SnowTile"; }
	CGameObject* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

