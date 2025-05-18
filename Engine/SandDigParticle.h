#pragma once
#include "TextureParticle.h"

BEGIN(Engine)
class  CSandDigParticle : public CTextureParticle
{
public:
	explicit CSandDigParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSandDigParticle(const CSandDigParticle& rhs);
	virtual ~CSandDigParticle();

	virtual void ResetParticle(Particle* particle) override;

	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CSandDigParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;

private:
	_float m_fRadius;
};
END

