#pragma once
#include "FloorTile.h"
class SandWaterArc :
	public CFloorTile
{
private:
	SandWaterArc(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~SandWaterArc();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SandWaterArc"; }
private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

