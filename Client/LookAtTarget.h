#pragma once
#include "Behavior.h"
class CLookAtTarget : public CBehavior
{
private:
	explicit CLookAtTarget(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLookAtTarget(const CLookAtTarget& rhs);
	virtual ~CLookAtTarget();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override;

public:
	static CComponent* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

