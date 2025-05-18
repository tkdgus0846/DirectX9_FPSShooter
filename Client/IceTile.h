#pragma once
#include "FloorTile.h"
class CIceTile :
	public CFloorTile
{
private:
	CIceTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIceTile();

public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"IceTile"; }


	
private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionEnter(const class Collision* collision);
	virtual void OnCollisionStay(const class Collision* collision);
	virtual void OnCollisionExit(const class Collision* collision);

	virtual void InteractGameObject(const InteractInfo* tInteractInfo) override;
private:
	_vec3	m_vDir;
};