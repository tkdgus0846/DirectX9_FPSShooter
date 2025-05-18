#pragma once
#include "FloorTile.h"
class FloorSmall421410 :
	public CFloorTile
{
public:
	FloorSmall421410(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorSmall421410();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorSmall421410"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

