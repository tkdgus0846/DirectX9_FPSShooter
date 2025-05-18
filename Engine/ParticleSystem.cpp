#include "stdafx.h"
#include "ParticleSystem.h"

#include "Export_Function.h"

CParticleSystem::CParticleSystem(LPDIRECT3DDEVICE9 pGraphicDev) :
	CComponent(pGraphicDev),
	m_BoundingBox({ 0.f,0.f,0.f }, { 0.f,0.f,0.f })
{
}

CParticleSystem::CParticleSystem(const CParticleSystem & rhs) :
	CComponent(rhs),
	m_VB(rhs.m_VB),
	m_VBSize(rhs.m_VBSize),
	m_VBOffset(rhs.m_VBOffset),
	m_VBBatchSize(rhs.m_VBBatchSize),
	m_Offset(rhs.m_Offset),
	m_EmitRate(rhs.m_EmitRate),
	m_Size(rhs.m_Size),
	m_BoundingBox(rhs.m_BoundingBox)
{
	m_VB->AddRef();
	/*m_Texture->AddRef();*/
	m_RenderOrder = 5;
}

CParticleSystem::~CParticleSystem()
{
}

_int CParticleSystem::Update_Component(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Component(fTimeDelta);
	if (iExit != 0) return iExit;

	_vec3 offsetPoint;
	m_pGameObject->m_pTransform->Get_Info(INFO_POS, &offsetPoint);


	m_BoundingBox.Offset(offsetPoint);
	m_Pos = offsetPoint + m_Offset;
	return 0;
}

void CParticleSystem::LateUpdate_Component()
{
}

void CParticleSystem::Render_Component()
{
	Render_Particle();
}

void CParticleSystem::SetNumParticle(const int & numParticle)
{
	for (int i = 0; i < numParticle; i++)
		AddParticle();
}

bool CParticleSystem::IsEmpty()
{
	return m_Particles.empty();
}

bool CParticleSystem::IsDead()
{
	bool ret;

	for (const Particle& it : m_Particles)
	{
		if (it.bIsAlive == true) return false;
	}

	return true;
}

void CParticleSystem::SetDead()
{
	for (Particle& it : m_Particles)
	{
		it.bIsAlive = false;
	}
}

void CParticleSystem::RemoveDeadParticles()
{
	list<Particle>::iterator it;

	it = m_Particles.begin();

	while (it != m_Particles.end())
	{
		if (it->bIsAlive == false)
		{
			it = m_Particles.erase(it);
		}
		else it++;
	}


}

void CParticleSystem::Reset()
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

void CParticleSystem::AddParticle()
{
	Particle particle;
	ResetParticle(&particle);
	m_Particles.push_back(particle);
}

void CParticleSystem::Free(void)
{
	m_VB->Release();
	CComponent::Free();
}

void CParticleSystem::PreRender()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, false);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE, FtoDw(m_Size));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.f));

	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.f));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.f));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.f));

	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	/*m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/
}

void CParticleSystem::PostRender()
{
	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
