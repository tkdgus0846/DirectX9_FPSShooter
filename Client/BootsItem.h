#pragma once
#include "Item.h"

BEGIN(Engine)

class CRcTex;

END

class CBootsItem :
	public CItem
{
private:
	CBootsItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBootsItem();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(_vec3 vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	D3DXMATRIX				matWorld, matView;
	_float					m_fAngle = 0.f;

public:
	static CBootsItem*	Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos);
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	virtual void OnCollisionStay(const class Collision* collision) final;

	void		WeaponRotationZ(const _float & fTimeDelta);

private:
	virtual void Free(void) override;
};