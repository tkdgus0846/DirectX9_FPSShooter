#include "stdafx.h"
#include "SmokeParticle.h"


#include "stdafx.h"
#include "Firework.h"
#include "GameObject.h"
#include "Transform.h"
#include "Export_Function.h"


CSmokeParticle::CSmokeParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CTextureParticle(pGraphicDev)
{
	m_Size = 0.7f;
	m_VBSize = 500;
	m_VBOffset = 0;
	m_VBBatchSize = 125;
}

CSmokeParticle::CSmokeParticle(const CSmokeParticle & rhs) :
	CTextureParticle(rhs)
{
	m_Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Smoke_Texture", nullptr));
	m_Texture->Set_Texture_Num(0);

}

CSmokeParticle::~CSmokeParticle()
{
}
