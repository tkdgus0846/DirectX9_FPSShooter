#pragma once
#include "Weapon.h"
class CSpreadWeapon :
	public CWeapon
{
public:
	explicit CSpreadWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSpreadWeapon();

public:
	// 발사할 위치. 
	virtual void Shot();
	CBullet*	Shot_Setting() { return nullptr; }
	CBullet*	Shot_Setting(_float fAngle);
	void		Set_bMainTain(_bool state) { m_bMaintain = state; }

	void		Set_Input() { m_bInput = true; }
	void		Init_Count() { m_iCount = 0; }
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;


	static CSpreadWeapon*		Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform);
	virtual void Free(void) override;

private:
	_float		m_fTime = 0.f;
	_bool		m_bShoot = true;
	_bool		m_bInput = false;
	_int		m_iCount = 0;
	_bool		m_bMaintain = false;
};