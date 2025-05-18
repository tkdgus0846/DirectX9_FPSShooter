#pragma once
#include "Behavior.h"

BEGIN(Engine)

class CBlackBoard;
class CSequence : public CBehavior
{
private:
	explicit CSequence(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSequence(const CSequence& rhs);
	virtual ~CSequence(); 
	
public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CSequence* Create(LPDIRECT3DDEVICE9 pGraphiDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

END