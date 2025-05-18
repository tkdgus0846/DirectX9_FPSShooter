#pragma once
#include "TextureParticle.h"

BEGIN(Engine)
class  CVortexParticle : public CTextureParticle
{
public:
	explicit CVortexParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVortexParticle(const CVortexParticle& rhs);
	virtual ~CVortexParticle();

	virtual void ResetParticle(Particle* particle) override;

	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CVortexParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;

private:
	_float m_fRadius;
};
END

