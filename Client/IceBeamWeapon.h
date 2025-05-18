#pragma once
#include "Weapon.h"

class CIceBeamWeapon : public CWeapon
{
protected:
	explicit CIceBeamWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIceBeamWeapon();

public:

	// 발사할 위치. 
	virtual CBullet* Shot_Setting() override;

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;


	static CIceBeamWeapon*		Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform);
	virtual void Free(void) override;
};

