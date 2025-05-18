#pragma once
#include "Behavior.h"

class CRangeInPlayer : public CBehavior
{
private:
	explicit CRangeInPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRangeInPlayer(const CRangeInPlayer& rhs);
	virtual ~CRangeInPlayer();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {}

	void Set_ReturnVal(_bool bSwitch) { m_bReturn = bSwitch; }

private:
	_bool m_bReturn;

public:
	static CRangeInPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

