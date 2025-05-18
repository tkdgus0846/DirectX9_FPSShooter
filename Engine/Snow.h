#pragma once
#include "TextureParticle.h"

BEGIN(Engine)

class  CSnow : public CTextureParticle
{
public:
	explicit CSnow(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSnow(const CSnow& rhs);
	virtual ~CSnow();

	virtual void ResetParticle(Particle* particle) override;



	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CSnow* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;

protected:
	virtual void Free(void) override;

};

END

