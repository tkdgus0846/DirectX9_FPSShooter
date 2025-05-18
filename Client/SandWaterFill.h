#pragma once
#include "FloorTile.h"
class SandWaterFill :
	public CFloorTile
{
private:
	SandWaterFill(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~SandWaterFill();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SandWaterFill"; }
private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

