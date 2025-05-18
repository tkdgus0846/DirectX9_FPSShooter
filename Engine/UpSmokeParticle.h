#pragma once
#include "SmokeParticle.h"

class CUpSmokeParticle : public CSmokeParticle
{
public:
	explicit CUpSmokeParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CUpSmokeParticle(const CUpSmokeParticle& rhs);
	virtual ~CUpSmokeParticle();

	virtual void ResetParticle(Particle* particle) override;
	virtual _int Update_Component(const _float& fTimeDelta) override;

	static CUpSmokeParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;
};

