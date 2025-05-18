#pragma once
#include "Behavior.h"

class CRandomLook : public CBehavior
{
private:
	explicit CRandomLook(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRandomLook(const CRandomLook& rhs);
	virtual ~CRandomLook();

public:
	virtual HRESULT Ready_Behavior();
	virtual _int	Update_Component(const _float& fTimeDelta);
	virtual void	LateUpdate_Component(void);
	virtual void	Render_Component(void);

	// Aircraft이면 x, y, z축을 보고 아니면 x, z만 본다.
	void Set_IsLook_Aircraft(_bool bSwitch = true) { m_bIsAircraft = bSwitch; }

private:
	_bool m_bIsAircraft;

public:
	static CRandomLook* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

