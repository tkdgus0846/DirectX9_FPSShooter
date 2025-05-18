#pragma once
#include "Behavior.h"

class CRangeCheck : public CBehavior
{
private:
	explicit CRangeCheck(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRangeCheck(const CRangeCheck& rhs);
	virtual ~CRangeCheck();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CRangeCheck* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

