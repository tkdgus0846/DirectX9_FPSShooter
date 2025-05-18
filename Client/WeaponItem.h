#pragma once
#include "Item.h"
class CWeaponItem :
	public CItem
{
private:
	CWeaponItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWeaponItem();

public:
	virtual HRESULT Add_Component();
	virtual HRESULT Ready_GameObject(_vec3 vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	virtual void OnCollisionStay(const class Collision* collision) final;

	void		Set_ID(WEAPONTYPE eID) { m_eID = eID; }

private:
	D3DXMATRIX				matWorld, matView;

public:
	static CWeaponItem*	Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, WEAPONTYPE eID);

private:
	virtual void Free(void) override;
	
	void		Select_Type();
	void		WeaponRotationZ(const _float & fTimeDelta);

private:
	WEAPONTYPE	m_eID = WEAPONEND;
	_float m_fAngle = 0.f;
};