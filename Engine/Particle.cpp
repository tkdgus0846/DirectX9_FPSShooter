#include "stdafx.h"
#include "Particle.h"
#include "Export_Function.h"
#include "ParticleMgr.h"


CParticle::CParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev),
	m_ParticleName(nullptr),
	m_Particle(nullptr)
{
	Set_LayerID(LAYER_PARTICLE);
	Set_ObjTag(L"Particle");
}

CParticle::~CParticle()
{
}

HRESULT CParticle::Add_Component()
{
	m_Particle = dynamic_cast<CParticleSystem*>(Engine::Clone_Proto(m_ParticleName, this, m_ParticleNum, m_Origin));
	m_uMapComponent[ID_ALL].insert({ m_ParticleName, m_Particle });

	return S_OK;
}

_int CParticle::Update_GameObject(const _float& fTimeDelta)
{
	if (m_Particle->IsDead()) 
		SetDead();

	if (GetDead()) 
		return OBJ_RETPOOL;
	
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	__super::Update_GameObject(fTimeDelta);
	
	Add_RenderGroup(RENDER_ALPHA, this);
	return OBJ_NOEVENT;
}

void CParticle::Render_GameObject(void)
{
	_matrix mat;
	mat.Identity();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &mat);

	__super::Render_GameObject();
}

void CParticle::SetBoundingSize(const _vec3& size)
{
	m_Particle->SetBoundingSize(size);
}

void CParticle::Reset()
{
	m_Particle->Reset();
}

void CParticle::SetDead(_bool bDead)
{
	__super::SetDead(bDead);

	if (bDead)
	{
		CParticleMgr::GetInstance()->Push(m_ParticleName, this);
		// 이펙트 풀로 다시 푸쉬해주는거 넣어야됨. m_TextureName 으로.
	}
}

CParticle* CParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* ParticleName, _int ParticleNum, const _vec3& Pos, const _vec3& Origin)
{
	CParticle* particle = new CParticle(pGraphicDev);
	NULL_CHECK_RETURN_MSG(particle, nullptr, L"파티클 생성실패");

	particle->m_ParticleName = ParticleName;
	particle->m_ParticleNum = ParticleNum;
	particle->m_Origin = Origin;
	particle->m_pTransform->m_vInfo[INFO_POS] = Pos;
	

	particle->Ready_GameObject();

	return particle;
}

void CParticle::Free(void)
{
	__super::Free();
}
