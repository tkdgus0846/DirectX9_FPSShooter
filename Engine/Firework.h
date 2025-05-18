#pragma once
#include "TextureParticle.h"

BEGIN(Engine)
class  CFirework : public CTextureParticle
{
public:
	explicit CFirework(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFirework(const CFirework& rhs);
	virtual ~CFirework();

	virtual void ResetParticle(Particle* particle) override;

	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CFirework* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;

private:
	_float m_fRadius;

private:
	virtual void PreRender() override;
	virtual void PostRender() override;

protected:
	virtual void Free(void) override;
};
END

