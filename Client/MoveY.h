#pragma once
#include "Behavior.h"

class CMoveY : public CBehavior
{
private:
	explicit CMoveY(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMoveY(const CMoveY& rhs);
	virtual ~CMoveY();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

	void Set_Dir_Up(const _float& fY = 4.f) { m_bIsUp = true; m_fDest = fY; }
	void Set_Dir_Down(const _float& fY = -10.f) { m_bIsUp = false; m_fDest = fY; }

private:
	_bool m_bIsUp;
	_bool m_bStart;
	_float m_fTime;
	_float m_fFstSpeed;
	_float m_fDest;

	const _float m_fMaxTime;

public:
	static CMoveY* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

