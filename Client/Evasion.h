#pragma once
#include "Behavior.h"

class CEvasion : public CBehavior
{
private:
	explicit CEvasion(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEvasion(const CEvasion& rhs);
	virtual ~CEvasion();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CEvasion* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

