#pragma once
#include "Behavior.h"
class CAttackToPlayer : public CBehavior
{
private:
	explicit CAttackToPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAttackToPlayer(const CAttackToPlayer& rhs);
	virtual ~CAttackToPlayer();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override;

	void Set_BulletSpeed(const _float& fSpeed) { m_fSpeed = fSpeed; }
	void Set_BulletKey(const _tchar* pKey) { m_pKey = pKey; }
	void Set_Scale(const _vec3& vScale) { m_vScale = vScale; }
	// 레이저 전용. 어택 포인트 출력하게 하는거임
	void Set_AttackPoint() { m_bAtkPoint = true; }

private:
	const _tchar* m_pKey;
	_float m_fSpeed;
	_vec3 m_vScale;
	_bool m_bAtkPoint;

public:
	static CAttackToPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

