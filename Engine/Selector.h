#pragma once
#include "Behavior.h"

BEGIN(Engine)

class CBlackBoard;
class CSelector : public CBehavior
{
private:
	explicit CSelector(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSelector(const CSelector& rhs);
	virtual ~CSelector();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CSelector* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

END