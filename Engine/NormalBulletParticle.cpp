#include "stdafx.h"
#include "NormalBulletParticle.h"

#include "Export_Function.h"


CNormalBulletParticle::CNormalBulletParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CColorParticle(pGraphicDev)
{
	m_Size = 0.3f;
	m_VBSize = 200;
	m_VBOffset = 0;
	m_VBBatchSize = 50;
}

CNormalBulletParticle::CNormalBulletParticle(const CNormalBulletParticle & rhs) :
	CColorParticle(rhs)
{
	m_fLifeTime = 0.15f;
	m_fAge = 0.f;
}

CNormalBulletParticle::~CNormalBulletParticle()
{
}

void CNormalBulletParticle::ResetParticle(Particle * particle)
{
	particle->bIsAlive = true;
	particle->vPos = m_Pos;
	
	_vec3 minVec = {-0.6f,-0.6f,-0.6f};
	_vec3 maxVec = { 0.6f,0.6f,0.6f };

	GetRandomVector(&particle->vVelocity, &minVec, &maxVec);
	particle->vVelocity += m_vNormalDir;

	particle->vVelocity.Normalize();
	particle->vVelocity *= GetRandomFloat(20.f, 40.f);

	particle->dwColor = D3DXCOLOR
		(0x38 / 255.f,
		0xb0 / 255.f,
		0xde / 255.f,
		GetRandomFloat(0.7f,1.f));

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
	particle->fLifeTime = GetRandomFloat(1.5f,2.5f);
}

_int CNormalBulletParticle::Update_Component(const _float & fTimeDelta)
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

CNormalBulletParticle * CNormalBulletParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNormalBulletParticle *	pInstance = new CNormalBulletParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Particle()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CNormalBulletParticle::Clone(void)
{
	return new CNormalBulletParticle(*this);
}

void CNormalBulletParticle::Reset()
{
	_vec3 offsetPoint;
	m_pGameObject->m_pTransform->Get_Info(INFO_POS, &offsetPoint);

	m_Pos = offsetPoint + m_Offset;

	m_fAge = 0.f;

	_matrix viewMat;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMat);
	viewMat.Inverse();

	_vec3 TempVec = { viewMat._41, viewMat._42, viewMat._43 };
	m_vNormalDir = TempVec - m_Pos;
	m_vNormalDir.Normalize();

	list<Particle>::iterator it;
	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		ResetParticle(&(*it));
	}
}
