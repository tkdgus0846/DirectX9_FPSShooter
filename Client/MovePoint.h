#pragma once
#include "Behavior.h"
class CMovePoint : public CBehavior
{
private:
	explicit CMovePoint(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMovePoint(const CMovePoint& rhs);
	virtual ~CMovePoint();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {};

private:
	_bool m_bStart;
	_vec3 m_vDest;
	_float m_fFstSpeed;

public:
	static CMovePoint* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

