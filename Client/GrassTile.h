#pragma once
#include "FloorTile.h"
class CGrassTile :
	public CFloorTile
{
private:
	CGrassTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGrassTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"GrassTile"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

