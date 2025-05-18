#pragma once
#include "SmokeParticle.h"
class CRunSmokeParticle : public CSmokeParticle
{
public:
	explicit CRunSmokeParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRunSmokeParticle(const CRunSmokeParticle& rhs);
	virtual ~CRunSmokeParticle();

	virtual void ResetParticle(Particle* particle) override;
	virtual _int Update_Component(const _float& fTimeDelta) override;

	static CRunSmokeParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;
};

