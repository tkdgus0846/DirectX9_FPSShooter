#pragma once
#include "FloorTile.h"
class CSandTile :
	public CFloorTile
{
private:
	CSandTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSandTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"CSandTile"; }
	CGameObject* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

