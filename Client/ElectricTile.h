#pragma once
#include "FloorTile.h"
class CElectricTile :
	public CFloorTile
{
private:
	CElectricTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CElectricTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ElectricTile"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

