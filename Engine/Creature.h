#pragma once
#include "GameObject.h"

class CCreature : public CGameObject
{
protected:
	explicit CCreature(LPDIRECT3DDEVICE9 pGrapicDev);
	virtual ~CCreature();

public:
	virtual HRESULT		Ready_GameObject(void);
	virtual _int		Update_GameObject(const _float& fTimeDelta);
	virtual void		LateUpdate_GameObject(void);
	virtual void		Render_GameObject(void);

	virtual void OnCollisionEnter(const class Collision* collsion);
	virtual void OnCollisionStay(const class Collision* collision);
	virtual void OnCollisionExit(const class Collision* collision);
	
public:
	virtual void	Get_Damaged(_int Damage)
	{
		if (GetDead()) return;

		m_iHp -= Damage;
		if (m_iHp <= 0)
		{
			m_iHp = 0;
			SetDead();
		}
	}
	_int	Get_Attack() const { return m_iAttack; }
	_int	Get_HP() const { return m_iHp; }
	_int	Get_MaxHP() const { return m_iMaxHp; }
	_float	Get_Speed() const { return m_fSpeed; }
	void	Set_Speed(const _float& speed) { m_fSpeed = speed; }

	void	Plus_Speed (_float fSpeed = 1) { m_fSpeed += fSpeed; }

protected:
	_float	m_fSpeed;
	_int	m_iMaxHp;
	_int	m_iHp;
	_int	m_iAttack;

protected:
	virtual void Free() override;
};

