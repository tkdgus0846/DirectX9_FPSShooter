#include "stdafx.h"
#include "UpSmokeParticle.h"


#include "Export_Function.h"


CUpSmokeParticle::CUpSmokeParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CSmokeParticle(pGraphicDev)
{
	m_Size = 1.5f;
	m_VBSize = 3; // 파티클 한번소환할때 먹는 버퍼사이즈
	m_VBOffset = 0;
	m_VBBatchSize = 3; // 파티클당 먹는ㄷ\사이즈
}

CUpSmokeParticle::CUpSmokeParticle(const CUpSmokeParticle & rhs) :
	CSmokeParticle(rhs)
{
}

CUpSmokeParticle::~CUpSmokeParticle()
{
}

void CUpSmokeParticle::ResetParticle(Particle * particle)
{
	particle->bIsAlive = true;

	particle->vPos.x = m_Pos.x + GetRandomFloat(-2.f, 2.f);
	particle->vPos.z = m_Pos.z + GetRandomFloat(-2.f, 2.f);
	particle->vPos.y = m_Pos.y;

	particle->fSpeed = GetRandomFloat(0.45f, 2.f);

	particle->fAge = 0.f;
	particle->fLifeTime = GetRandomFloat(1.0f, 2.f);
}

_int CUpSmokeParticle::Update_Component(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Component(fTimeDelta);
	if (iExit != 0) return iExit;

	list<Particle>::iterator it;

	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		if (it->bIsAlive)
		{

			/*it->vPos.x = m_Pos.x + it->fRadius * cosf(it->fAngle);
			it->vPos.z = m_Pos.z + it->fRadius * sinf(it->fAngle);*/

			it->fAge += fTimeDelta;
			it->vPos.y += it->fSpeed * fTimeDelta;
			if (it->vPos.y < 0.1f) it->vPos.y = 0.1f;
			
			if (it->fAge > it->fLifeTime)
				it->bIsAlive = false;
		}
	}
	return 0;
}

CUpSmokeParticle * CUpSmokeParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CUpSmokeParticle *	pInstance = new CUpSmokeParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Particle()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CUpSmokeParticle::Clone(void)
{
	return new CUpSmokeParticle(*this);
}
