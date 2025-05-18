#pragma once
#include "Component.h"

BEGIN(Engine)

class CRigidbody : public CComponent
{
private:
	explicit CRigidbody(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRigidbody(const CRigidbody& rhs);
	virtual ~CRigidbody();

public:
	HRESULT Ready_Rigidbody(void);
	virtual _int Update_Component(const _float& fTimeDelta);
	virtual void LateUpdate_Component(void);

	static CRigidbody* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

public: 
	void		Collision_OtherBody(CRigidbody* otherBody, const Collision* collision);

private:
	_vec3		m_vVelocity;
	_vec3		m_vMoveDir;
	_vec3		m_vPrevPos;
	_vec3		m_vCurPos;

	_float		m_fSpeed;
	_int		m_Force;

private:
	virtual void Free(void) override;
};

END