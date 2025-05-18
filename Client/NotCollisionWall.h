#pragma once
#include "Behavior.h"

class CNotCollisionWall : public CBehavior
{
private:
	explicit CNotCollisionWall(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CNotCollisionWall(const CNotCollisionWall& rhs);
	virtual ~CNotCollisionWall();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CNotCollisionWall* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

