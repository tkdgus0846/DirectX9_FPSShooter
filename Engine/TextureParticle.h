#pragma once
#include "ParticleSystem.h"

BEGIN(Engine)

class  CTextureParticle : public CParticleSystem
{
protected:
	explicit CTextureParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTextureParticle(const CTextureParticle& rhs);
	virtual ~CTextureParticle();
public:
	virtual HRESULT		Ready_Particle(void) override;	
	virtual void Free(void) override;

private:
	virtual void		Render_Particle(void) override;

protected:
	class CTexture*			m_Texture;
};

END

