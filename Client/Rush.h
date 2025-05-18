#pragma once
#include "Behavior.h"
class CRush : public CBehavior
{
private:
	explicit CRush(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRush(const CRush& rhs);
	virtual ~CRush();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {};
	virtual void Render_Component(void) override {};

public:
	static CRush* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

