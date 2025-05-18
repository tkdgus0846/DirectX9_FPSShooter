#pragma once
#include "Behavior.h"

BEGIN(Engine)

class CBlackBoard;
class CRoot : public CBehavior
{
private:
	explicit CRoot(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRoot(const CRoot& rhs);
	virtual ~CRoot();

public:
	virtual HRESULT Ready_Behavior(void) override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CRoot* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void);

private:
	virtual void Free() override;
};

END