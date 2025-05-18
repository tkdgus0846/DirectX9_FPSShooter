#pragma once
#include "FloorTile.h"
#include "IInteractableTile.h"
class CNullFloorTile :
	public CFloorTile
{
private:
	CNullFloorTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNullFloorTile();

public:

public:
	HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static CNullFloorTile* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos);

	static const _tchar* Tag() { return L"CNullFloorTile"; }

private:
	virtual HRESULT Add_Component() override;
};

