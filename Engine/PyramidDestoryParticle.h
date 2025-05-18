#pragma once
#include "ColorParticle.h"

class CPyramidDestoryParticle : public CColorParticle
{
public:
	explicit CPyramidDestoryParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPyramidDestoryParticle(const CPyramidDestoryParticle& rhs);
	virtual ~CPyramidDestoryParticle();

	virtual void ResetParticle(Particle* particle) override;

	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CPyramidDestoryParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;


	virtual void Reset() override;

private:
	_float	m_fLifeTime;
	_float	m_fAge;
};

