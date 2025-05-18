#include "stdafx.h"
#include "JumpSmokeParticle.h"

#include "Export_Function.h"


CJumpSmokeParticle::CJumpSmokeParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CSmokeParticle(pGraphicDev)
{
	m_Size = 0.6f;
}

CJumpSmokeParticle::CJumpSmokeParticle(const CJumpSmokeParticle & rhs) :
	CSmokeParticle(rhs)
{
}

CJumpSmokeParticle::~CJumpSmokeParticle()
{
}

void CJumpSmokeParticle::ResetParticle(Particle * particle)
{
	particle->bIsAlive = true;

	particle->vPos.x = m_Pos.x + 5.f * cosf(D3DXToRadian(GetRandomFloat(0.f, 360.f)));
	particle->vPos.z = m_Pos.z + 5.f * sinf(D3DXToRadian(GetRandomFloat(0.f, 360.f)));
	particle->vPos.y = m_Pos.y - 1.1f;

	particle->fSpeed = 2.f;

	particle->fAge = 0.f;
	particle->fLifeTime = 1.5f;
}

_int CJumpSmokeParticle::Update_Component(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Component(fTimeDelta);
	if (iExit != 0) return iExit;

	list<Particle>::iterator it;

	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		if (it->bIsAlive)
		{
			//it->fAge += fTimeDelta * 7.f;

			_float fY = it->fSpeed * it->fAge - 4.9f * it->fAge * it->fAge;

			/*it->vPos.x = m_Pos.x;
			it->vPos.z = m_Pos.z;*/
			it->vPos.y -= fY / 8.f;

			it->fAge += fTimeDelta;

			if (it->fAge > it->fLifeTime)
				it->bIsAlive = false;
		}
		else
		{
			ResetParticle(&*it);
		}
	}
	return 0;
}

CJumpSmokeParticle * CJumpSmokeParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CJumpSmokeParticle *	pInstance = new CJumpSmokeParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Particle()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CJumpSmokeParticle::Clone(void)
{
	return new CJumpSmokeParticle(*this);
}