#pragma once
#include "FloorTile.h"

class CLavaTile : public CFloorTile
{
private:
	CLavaTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLavaTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"LavaTile"; }
	CGameObject* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);


	virtual void SetDead(_bool bDead = true) override;

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
protected:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;

private:
	_float		m_fTime;
	_float		m_fMaxTime;

};

