#pragma once

#include "Behavior.h"

class CTimeInLimit : public CBehavior
{
private:
	explicit CTimeInLimit(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTimeInLimit(const CTimeInLimit& rhs);
	virtual ~CTimeInLimit();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

private:
	_bool m_bIsCall;

public:
	static CTimeInLimit* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

