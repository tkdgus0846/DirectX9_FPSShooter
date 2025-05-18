#pragma once
#include "SmokeParticle.h"

class CJumpSmokeParticle : public CSmokeParticle
{
public:
	explicit CJumpSmokeParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CJumpSmokeParticle(const CJumpSmokeParticle& rhs);
	virtual ~CJumpSmokeParticle();

	virtual void ResetParticle(Particle* particle) override;
	virtual _int Update_Component(const _float& fTimeDelta) override;

	static CJumpSmokeParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;

};

