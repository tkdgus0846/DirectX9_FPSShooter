#pragma once
#include "ColorParticle.h"

class CVentParticle : public CColorParticle
{
public:
	explicit CVentParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVentParticle(const CVentParticle& rhs);
	virtual ~CVentParticle();

	virtual void ResetParticle(Particle* particle) override;

	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CVentParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;


	virtual void Reset() override;

private:
	_float		m_fUpPower;
	
};

