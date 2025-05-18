#include "stdafx.h"
#include "PyramidDestoryParticle.h"

#include "Export_Function.h"


CPyramidDestoryParticle::CPyramidDestoryParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CColorParticle(pGraphicDev)
{
	m_Size = 0.3f;
	m_VBSize = 50;
	m_VBOffset = 0;
	m_VBBatchSize = 50;
}

CPyramidDestoryParticle::CPyramidDestoryParticle(const CPyramidDestoryParticle & rhs) :
	CColorParticle(rhs)
{
	m_fLifeTime = 1.5f;
	m_fAge = 0.f;
}

CPyramidDestoryParticle::~CPyramidDestoryParticle()
{
}

void CPyramidDestoryParticle::ResetParticle(Particle * particle)
{
	particle->bIsAlive = true;
	particle->vPos = m_Pos;

	_vec3 minVec = { -1.0f,-1.0f,-1.0f };
	_vec3 maxVec = { 1.0f,1.0f,1.0f };

	GetRandomVector(&particle->vVelocity, &minVec, &maxVec);
	particle->vVelocity.Normalize();
	particle->vVelocity *= GetRandomFloat(0.1f, 2.f);

	particle->dwColor = D3DXCOLOR
		(0xb9 / 255.f,
		0x7a / 255.f,
		0x57 / 255.f,
		GetRandomFloat(0.3f, 0.8f));

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
	particle->fLifeTime = GetRandomFloat(1.5f, 2.5f);
}

_int CPyramidDestoryParticle::Update_Component(const _float & fTimeDelta)
{
	if (m_fAge > m_fLifeTime)
	{
		SetDead();
		return 0;
	}

	_int iExit = __super::Update_Component(fTimeDelta);
	if (iExit != 0) return iExit;



	list<Particle>::iterator it;
	m_fAge += fTimeDelta;

	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		if (it->bIsAlive)
		{
			it->vPos += fTimeDelta * it->vVelocity;
			/*it->fAge += fTimeDelta;
			if (it->fAge > it->fLifeTime)
			it->bIsAlive = false;*/

		}

	}
	return 0;
}

CPyramidDestoryParticle * CPyramidDestoryParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPyramidDestoryParticle *	pInstance = new CPyramidDestoryParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Particle()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CPyramidDestoryParticle::Clone(void)
{
	return new CPyramidDestoryParticle(*this);
}

void CPyramidDestoryParticle::Reset()
{
	_vec3 offsetPoint;
	m_pGameObject->m_pTransform->Get_Info(INFO_POS, &offsetPoint);

	m_Pos = offsetPoint + m_Offset;
	m_fAge = 0.f;

	list<Particle>::iterator it;
	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		ResetParticle(&(*it));
	}
}

