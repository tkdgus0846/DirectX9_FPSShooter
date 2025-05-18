#pragma once
#include "ColorParticle.h"

class CNormalBulletParticle : public CColorParticle
{
public:
	explicit CNormalBulletParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CNormalBulletParticle(const CNormalBulletParticle& rhs);
	virtual ~CNormalBulletParticle();

	virtual void ResetParticle(Particle* particle) override;

	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CNormalBulletParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;


	virtual void Reset() override;

private:
	_float	m_fLifeTime;
	_float	m_fAge;
	_vec3	m_vNormalDir;
};

