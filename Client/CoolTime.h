#pragma once
#include "Behavior.h"
class CCoolTime : public CBehavior
{
private:
	explicit CCoolTime(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCoolTime(const CCoolTime& rhs);
	virtual ~CCoolTime();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {}

private:
	_bool m_bIsCall;

public:
	static CCoolTime* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

