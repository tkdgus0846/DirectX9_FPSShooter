#pragma once
#include "Behavior.h"

class CParabola : public CBehavior
{
private:
	explicit CParabola(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CParabola(const CParabola& rhs);
	virtual ~CParabola();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override;

private:
	_vec3 m_vDir;	// y 성분을 제외한 이동 방향.
	_float m_fTime;
	_float m_fForce;
	_float m_FstSpeed;
	_bool  m_bStart;

public:
	static CParabola* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

