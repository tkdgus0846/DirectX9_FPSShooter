#include "stdafx.h"
#include "Firework.h"
#include "GameObject.h"
#include "Transform.h"
#include "Export_Function.h"


CFirework::CFirework(LPDIRECT3DDEVICE9 pGraphicDev) :
	CTextureParticle(pGraphicDev)
{
	m_Size = 0.7f;
	m_VBSize = 2048;
	m_VBOffset = 0;
	m_VBBatchSize = 512;
}

CFirework::CFirework(const CFirework & rhs) :
	CTextureParticle(rhs)
{
	m_fRadius = 10.f;

	m_Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"IceBullet_Texture", nullptr));
	
}

CFirework::~CFirework()
{
}

void CFirework::ResetParticle(Particle * particle)
{
	_vec3 offsetPoint;
	m_pGameObject->m_pTransform->Get_Info(INFO_POS, &offsetPoint);

	/*m_BoundingBox.Offset(offsetPoint);*/
	m_Pos = offsetPoint;

	particle->bIsAlive = true;

	particle->fAngle = D3DXToRadian(GetRandomFloat(0.f, 360.f));
	particle->fRadius = GetRandomFloat(15.f, 20.f);
	particle->vPos.x = m_Pos.x + particle->fRadius * cosf(D3DXToRadian(particle->fAngle));
	particle->vPos.z = m_Pos.z + particle->fRadius * sinf(D3DXToRadian(particle->fAngle));
	particle->vPos.y = m_Pos.y - 2.1f;

	particle->fSpeed = 0.45f;

	particle->vTexUV = { 0.f, 0.f };
	particle->fAge = 0.f;
	particle->fLifeTime = 7.5f;
}

_int CFirework::Update_Component(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Component(fTimeDelta);
	if (iExit != 0) return iExit;

	list<Particle>::iterator it;
	m_fRadius -= 1.0f * fTimeDelta;

	for (it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		if (it->bIsAlive)
		{
			
			it->vPos.x = m_Pos.x + it->fRadius * cosf(it->fAngle);
			it->vPos.z = m_Pos.z + it->fRadius * sinf(it->fAngle);

			it->fAge += fTimeDelta;
			it->vPos.y -= it->fSpeed * fTimeDelta;
			if (it->vPos.y < 0.1f) it->vPos.y = 0.1f;
			it->fAngle -= D3DXToRadian(480.f) * fTimeDelta;
			it->fRadius -= GetRandomFloat(3.f,9.f) * fTimeDelta;
			/*if (it->fRadius < 8.f) it->fRadius = 8.f;*/
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

CFirework * CFirework::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFirework *	pInstance = new CFirework(pGraphicDev);

	if (FAILED(pInstance->Ready_Particle()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CFirework::Clone(void)
{
	return new CFirework(*this);
}

void CFirework::PreRender()
{
	CTextureParticle::PreRender();

	/*m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);*/
	//m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void CFirework::PostRender()
{
	CTextureParticle::PostRender();
	//m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void CFirework::Free(void)
{
	__super::Free();
}
