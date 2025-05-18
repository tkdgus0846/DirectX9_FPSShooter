#pragma once
#include "Behavior.h"
class CBigJump : public CBehavior
{
private:
	explicit CBigJump(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBigJump(const CBigJump& rhs);
	virtual ~CBigJump();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override;

	void Set_Force(const _float& fForce) { m_fForce = fForce; }
	void Set_Stop(_bool bSwitch) { m_bSetStop = bSwitch; m_bStop = bSwitch; }

private:
	_float m_fTime;
	_float m_fForce;
	_float m_fInit;
	_bool m_bStop;
	_bool m_bSetStop;
	_bool m_bJump;

public:
	static CBigJump* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

