#pragma once
#include "FloorTile.h"

// 기본 구멍 타일
class FloorHole421777 : public CFloorTile
{
public:
	FloorHole421777(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorHole421777();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorHole421777"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

