#pragma once
#include "Weapon.h"

class CSwordWeapon : public CWeapon
{
protected:
	explicit CSwordWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSwordWeapon();

public:

	CBullet*			Shot_Setting() { return nullptr; }
	// 발사할 위치.
	void				Gather_Sword(const _float& fTimeDelta);
	virtual void		Shot() override;
	CBullet*			Sword_Shot_Setting(_int iIndex);

	virtual _int		Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT		Add_Component() override;
	virtual HRESULT		Ready_GameObject(void) override;
	virtual void		LateUpdate_GameObject(void) override;
	virtual void		Render_GameObject(void) override;


	static CSwordWeapon*		Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform);
	virtual void Free(void) override;

private:
	_vec3	m_OffsetArr[5];
	_vec3	m_PosArr[5];
	_bool	m_SwordPreparedArr[5];

	_float	m_fGatherTime;
	_int	m_GatheredSword;

	vector<CBullet*>	m_SwordBulletArr;
};

