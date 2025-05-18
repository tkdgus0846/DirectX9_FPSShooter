#pragma once
#include "ParticleSystem.h"

BEGIN(Engine)

class  CColorParticle : public CParticleSystem
{
protected:
	explicit CColorParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CColorParticle(const CColorParticle& rhs);
	virtual ~CColorParticle();

public:
	virtual HRESULT		Ready_Particle(void) override;

private:
	virtual void		Render_Particle(void) override;
};

END

