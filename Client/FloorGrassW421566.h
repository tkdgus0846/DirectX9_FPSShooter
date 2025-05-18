#pragma once
#include "FloorTile.h"
class FloorGrassW421566 :
	public CFloorTile
{
public:
	FloorGrassW421566(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorGrassW421566();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorGrassW421566"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

