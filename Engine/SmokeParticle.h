#pragma once
#include "TextureParticle.h"

class CSmokeParticle : public CTextureParticle
{
public:
	explicit CSmokeParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSmokeParticle(const CSmokeParticle& rhs);
	virtual ~CSmokeParticle();
};

