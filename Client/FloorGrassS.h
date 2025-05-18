#pragma once
#include "FloorTile.h"
class FloorGrassS :
	public CFloorTile
{
public:
	FloorGrassS(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorGrassS();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorGrassS"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};