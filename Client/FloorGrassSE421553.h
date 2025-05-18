#pragma once
#include "FloorTile.h"
class FloorGrassSE421553 :
	public CFloorTile
{
public:
	FloorGrassSE421553(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorGrassSE421553();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorGrassSE421553"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

