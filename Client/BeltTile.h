#pragma once
#include "FloorTile.h"

class CBeltTile :
	public CFloorTile
{
public:
	CBeltTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBeltTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"BeltTile"; }

public:
	virtual void InteractGameObject(const InteractInfo* tInteractInfo);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

