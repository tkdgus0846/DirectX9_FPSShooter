#pragma once
#include "FloorTile.h"
class SandWaterLine
	: public CFloorTile
{
private:
	SandWaterLine(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~SandWaterLine();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SandWaterLine"; }
private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

