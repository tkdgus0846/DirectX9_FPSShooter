#pragma once
#include "GameObject.h"

class CWeapon : public CGameObject
{
	friend class CSwordWeapon;

protected:
	explicit CWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWeapon();

public:
	virtual void	Shot();
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;

	_int	Get_CurBulletNum() const { return m_CurBulletNum; }
	_int	Get_MaxBulletNum() const { return m_MaxBulletNum; }
	_bool	Is_BulletEmpty() const { return (m_CurBulletNum == 0) ? true : false; }
	void	SpendBullet(_int bulletNum = 1)
	{
		m_CurBulletNum -= bulletNum;
		if (m_CurBulletNum < 0)  m_CurBulletNum = 0;
	}
	void	GainBullet(_int bulletNum = 1)
	{
		m_CurBulletNum += bulletNum;
		if (m_CurBulletNum > m_MaxBulletNum) m_CurBulletNum = m_MaxBulletNum;
	}

	void	Set_TacticalScopeOn(_vec3 vDir) { m_bTacticalScope = true; m_TacticalDir = vDir; }
	void	Set_TacticalScopeOff() { m_bTacticalScope = false;}

	_bool	Get_TacticalScope() { return m_bTacticalScope ; }

private:
	_float	m_fAccTime;
	

protected:
	_int	m_MaxBulletNum; // 가질 수 있는 총알 최대량
	_int	m_CurBulletNum; // 현재 총알 수

	_float	m_fCycle;		// 총을 쏠 수 있는 주기
	_bool	m_bShooted;		// 쏘고나서 true로 만들어주면됨.
	_bool	m_bEnableShot;	// true일때만 Shot()이 발동함.

	class CTransform* m_pOwnerTransform;
	_vec3	m_vOffsetTrans;

	_bool	m_bTacticalScope = false;
	_vec3	m_TacticalDir;


protected:
	virtual class CBullet*	Shot_Setting() PURE;
	_bool	CanShot() const { return m_bEnableShot && !Is_BulletEmpty(); }
};

