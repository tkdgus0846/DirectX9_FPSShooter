#pragma once
#include "FloorTile.h"
class FloorGrassW :
	public CFloorTile
{
public:
	FloorGrassW(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorGrassW();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorGrassW"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

