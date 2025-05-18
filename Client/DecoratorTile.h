#pragma once
#include "FloorTile.h"

class CDecoratorTile :
	public CFloorTile
{
private:
	CDecoratorTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CDecoratorTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"DecoratorTile"; }
private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};