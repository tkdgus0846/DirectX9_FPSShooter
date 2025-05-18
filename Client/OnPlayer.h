#pragma once
#include "Behavior.h"
class COnPlayer : public CBehavior
{
private:
	explicit COnPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit COnPlayer(const COnPlayer& rhs);
	virtual ~COnPlayer();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static COnPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

