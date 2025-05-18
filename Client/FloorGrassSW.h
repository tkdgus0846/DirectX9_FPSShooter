#pragma once
#include "FloorTile.h"
class FloorGrassSW :
	public CFloorTile
{
public:
	FloorGrassSW(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorGrassSW();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorGrassSW"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

