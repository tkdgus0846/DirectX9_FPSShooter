#pragma once
#include "Behavior.h"

class CWormMoveCtrl : public CBehavior
{
private:
	explicit CWormMoveCtrl(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWormMoveCtrl(const CWormMoveCtrl& rhs);
	virtual ~CWormMoveCtrl();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {}

	void Set_Stop() { m_bStart = false; }
	void Set_Move() { m_bStart = true; }

private:
	_bool  m_bStart;

public:
	static CWormMoveCtrl* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

