#pragma once
#include "Behavior.h"
class CLookAtPlayer : public CBehavior
{
private:
	explicit CLookAtPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLookAtPlayer(const CLookAtPlayer& rhs);
	virtual ~CLookAtPlayer();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {};

private:
	_bool m_bStart;
	_float m_fTime;
	_float m_fFstSpeed;

public:
	static CLookAtPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

