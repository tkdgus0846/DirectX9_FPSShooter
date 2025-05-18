#include "stdafx.h"
#include "SandStorm.h"
#include "Export_Utility.h"



CSandStorm::CSandStorm(LPDIRECT3DDEVICE9 pGraphicDev) :
	CTextureParticle(pGraphicDev)
{
	m_BoundingBox = BoundingBox();
	m_Size = 0.13f;
	m_VBSize = 2000;
	m_VBOffset = 0;
	m_VBBatchSize = 500;
}

CSandStorm::CSandStorm(const CSandStorm& rhs) :
	CTextureParticle(rhs)
{
	for (auto it = rhs.m_Particles.begin(); it != rhs.m_Particles.end(); it++)
		m_Particles.push_back(*it);

	m_Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SandStorm_Texture", nullptr));
	m_Texture->Set_Texture_Num(0);
}

CSandStorm::~CSandStorm()
{

}

void CSandStorm::ResetParticle(Particle* particle)
{
	particle->bIsAlive = true;

	_vec3 vMax = m_BoundingBox._max;
	vMax.y = (m_BoundingBox._min.y + m_BoundingBox._max.y) / 2.f;
	GetRandomVector(
		&particle->vPos,
		&m_BoundingBox._min,
		&vMax);

	/*particle->vPos.y = m_BoundingBox._max.y;*/

	_vec3 centerPos = m_BoundingBox.Get_Center();
	centerPos.y -= 20.f;
	_vec3 dir = centerPos - particle->vPos;
	_vec3 minVec = { -1.f,-0.05f,-1.f };
	_vec3 maxVec = { 1.f,0.0f,1.f };

	

	GetRandomVector(
		&dir,
		&minVec,
		&maxVec
		);

	dir.Normalize();
	particle->vVelocity.x = dir.x * GetRandomFloat(0.5f, 1.0f) * 45.f;
	particle->vVelocity.y = dir.y;
	particle->vVelocity.z = dir.z * GetRandomFloat(0.5f, 1.0f) * 45.f;

	
}

_int CSandStorm::Update_Component(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Component(fTimeDelta);
	if (iExit != 0) return iExit;

	list<Particle>::iterator it;

	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		it->vPos += it->vVelocity * fTimeDelta;

		//cout << ":::::::" << it->vPos.x << " " << it->vPos.y << " " << it->vPos.z << endl;
		if (m_BoundingBox.Intersect(it->vPos) == false)
		{
			ResetParticle(&(*it));
		}
	}
	return 0;
}

CSandStorm* CSandStorm::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSandStorm *	pInstance = new CSandStorm(pGraphicDev);

	if (FAILED(pInstance->Ready_Particle()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

Engine::CComponent* CSandStorm::Clone(void)
{
	return new CSandStorm(*this);
}

void CSandStorm::Free(void)
{
	__super::Free();
}

