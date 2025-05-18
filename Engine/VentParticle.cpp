#include "stdafx.h"
#include "VentParticle.h"
#include "Export_Function.h"


CVentParticle::CVentParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CColorParticle(pGraphicDev)
{
	m_Size = 0.6f;
	m_VBSize = 100;
	m_VBOffset = 0;
	m_VBBatchSize = 100;

	m_fUpPower = 2.f;
}

CVentParticle::CVentParticle(const CVentParticle & rhs) :
	CColorParticle(rhs),
	m_fUpPower(rhs.m_fUpPower)
{
}

CVentParticle::~CVentParticle()
{
}

void CVentParticle::ResetParticle(Particle * particle)
{
	particle->bIsAlive = true;

	particle->vPos.x = m_Pos.x + GetRandomFloat(-5.f, 5.f);
	particle->vPos.z = m_Pos.z + GetRandomFloat(-5.f, 5.f);
	particle->vPos.y = m_Pos.y + GetRandomFloat(-5.f, 0.f);

	_vec3 minVec = { -0.2f,1.0f,-0.2f };
	_vec3 maxVec = { 0.2f,6.0f,0.2f };

	GetRandomVector(&particle->vVelocity, &minVec, &maxVec);
	particle->vVelocity.Normalize();
	particle->vVelocity *= GetRandomFloat(5.1f, 10.f);
	//particle->fSpeed = GetRandomFloat(0.9f, 2.9f);

	particle->dwColor = D3DXCOLOR
	(	1.f,
		1.f,
		1.f,
		GetRandomFloat(0.7f, 1.0f)
	);

	/*particle->dwColor = D3DXCOLOR
	(GetRandomFloat(0.0f, 1.f),
	GetRandomFloat(0.0f, 1.f),
	GetRandomFloat(0.0f, 1.f),
	GetRandomFloat(0.5f, 1.f));*/
	/*particle->dwColor = D3DXCOLOR
	(1.f,
	0.f,
	0.f,
	GetRandomFloat(0.5f, 1.f));*/

	particle->fAge = 0.f;
	particle->fLifeTime = GetRandomFloat(1.0f, 2.5f);
	
}

_int CVentParticle::Update_Component(const _float & fTimeDelta)
{
	
	_int iExit = __super::Update_Component(fTimeDelta);
	if (iExit != 0) return iExit;



	list<Particle>::iterator it;

	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		if (it->bIsAlive)
		{
			it->vPos += fTimeDelta * it->vVelocity;
		
			it->fAge += fTimeDelta;
			

			if (it->fAge > it->fLifeTime)
				it->bIsAlive = false;
		}
		/*else
		{
			ResetParticle(&*it);
		}*/
	}
	return 0;
}

CVentParticle * CVentParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVentParticle *	pInstance = new CVentParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Particle()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CVentParticle::Clone(void)
{
	return new CVentParticle(*this);
}

void CVentParticle::Reset()
{
	_vec3 offsetPoint;
	m_pGameObject->m_pTransform->Get_Info(INFO_POS, &offsetPoint);

	m_Pos = offsetPoint + m_Offset;

	list<Particle>::iterator it;
	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		ResetParticle(&(*it));
	}
}
