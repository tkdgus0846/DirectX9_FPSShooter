#pragma once
#include "TextureParticle.h"

class CSandStorm : public CTextureParticle
{
public:
	explicit CSandStorm(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSandStorm(const CSandStorm& rhs);
	virtual ~CSandStorm();

	virtual void ResetParticle(Particle* particle) override;



	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CSandStorm* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;

protected:
	virtual void Free(void) override;
};

