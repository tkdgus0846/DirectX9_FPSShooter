#pragma once
#include "Behavior.h"

class CJump : public CBehavior
{
private:
	explicit CJump(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CJump(const CJump& rhs);
	virtual ~CJump();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override;

	void Set_Force(const _float& fForce) { m_fForce = fForce; }

private:
	_float m_fTime;
	_float m_fForce;
	_float m_fInit;

public:
	static CJump* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

