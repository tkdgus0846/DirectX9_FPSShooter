#include "VortexBullet.h"
#include "BulletMgr.h"
#include "Monster.h"
#include "Effect.h"
#include "EffectManager.h"

#include "Export_Function.h"

CVortexBullet::CVortexBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	Set_ObjTag(L"VortexBullet");
	m_fSpeed = 20.f;
	m_fLifeSpan = 7.f;
	m_fAge = 0.f;
	m_Damage = 0;
}

CVortexBullet::~CVortexBullet()
{

}

void CVortexBullet::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
		CBulletMgr::GetInstance()->Push(L"VortexBullet", this);
}

HRESULT CVortexBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CVortexBullet::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead()) return OBJ_RETPOOL;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	_matrix viewMat;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMat);
	//m_pTransform->Set_Billboard(&viewMat);

	__super::Update_GameObject(fTimeDelta);

	if (m_bHit == false)
	{
		m_Animation->Update_Component(fTimeDelta);
		m_pTransform->Move_Walk(m_fSpeed*2.f, fTimeDelta);
	}
	else
	{
		m_Particle->Update_Component(fTimeDelta);
		/*if (m_pTransform->m_vInfo[INFO_POS].y > 0.02f)
		{
			m_pTransform->m_vInfo[INFO_POS].y -= 1.1f*fTimeDelta;
		}*/

		if (m_pTransform->m_vScale.x < 8.f)
		{
			m_pTransform->m_vScale.x += 4.f*fTimeDelta;
			m_pTransform->m_vScale.y += 4.f*fTimeDelta;
		}

		
		m_pTransform->Rot_Roll(-360.f, fTimeDelta*1.5f);
		//m_pTransform->Rot_Axis({})
		// y ÃàÀ¸·Î »±»±µµ´ÂÄÚµå ³Ö¾î¾ßµÊ.
		
	}
		
	Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CVortexBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();

	if (m_bHit == false)
		m_Animation->LateUpdate_Component();
}

void CVortexBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	
	__super::Render_GameObject();

	if (m_bHit == false)
		m_Animation->Render_Component();
	else
	{	
		m_AfterTexture->Render_Component();
	}
		

	m_RcTex->Render_Component();

	if (m_bHit == true)
	{
		_matrix mat;
		mat.Identity();
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &mat);
		m_Particle->Render_Component();
	}
		
}

void CVortexBullet::OnCollisionEnter(const Collision * collsion)
{
	if (m_bHit == true) return;

	if (dynamic_cast<CMonster*>(collsion->OtherGameObject) != nullptr && collsion->MyCollider == Get_Component(L"BodyCollider", ID_ALL) && 
		collsion->OtherCollider == collsion->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		if (m_bHit == false)
		{
			m_bHit = true;
			m_pTransform->Set_Scale({ 0.5f,0.5f,1.f });
			
			m_pTransform->Set_Dir({ 0.f,0.f,1.f });
			m_pTransform->Rot_Pitch(90.f, 1.f);
			m_pTransform->m_vInfo[INFO_POS].y = 0.03f;
		}
	}
	
}

void CVortexBullet::OnCollisionStay(const Collision * collision)
{
	
	if (m_bHit == true)
	{
		if (collision->MyCollider == Get_Component(L"RangeCollider", ID_ALL) &&
			dynamic_cast<CMonster*>(collision->OtherGameObject) != nullptr &&
			collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL) == collision->OtherCollider)
		{
			// ²ø¿© ´ç°ÜÁÖ´Â ÄÚµå.

			_vec3 dir = m_pTransform->m_vInfo[INFO_POS] - collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS];
			
			//dir.y = 0.f;
			dir.Normalize();

			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS] += dir * 0.1f;
			
		}
	}
}

void CVortexBullet::OnCollisionExit(const Collision * collision)
{
}

HRESULT CVortexBullet::Add_Component()
{
	m_AfterTexture  =  dynamic_cast<CTexture*>(Engine::Clone_Proto(L"VortexBulletAfter_Texture", this));
	NULL_CHECK_RETURN(m_AfterTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"VortexBulletAfter_Texture", m_AfterTexture });

	m_BeforeTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"VortexBulletBefore_Texture", this));
	NULL_CHECK_RETURN(m_BeforeTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"VortexBulletBefore_Texture", m_BeforeTexture });

	m_Animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_Animation, E_FAIL);

	m_Animation->BindAnimation(ANIM_SHOT, m_BeforeTexture, 0.1f);
	m_Animation->SelectState(ANIM_SHOT);
	m_uMapComponent[ID_STATIC].insert({ L"Animation", m_Animation });

	m_RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_RcTex, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"RcTex", m_RcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_PLAYERBULLET));
	pCollider->Set_BoundingBox({ 1.5f, 1.5f, 1.5f });
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"RangeCollider", this, COL_PLAYERBULLET));
	pCollider->Set_BoundingBox({ 100.5f, 20.5f, 100.5f });
	m_uMapComponent[ID_ALL].insert({ L"RangeCollider", pCollider });

	
	m_Particle = dynamic_cast<CTextureParticle*>(Engine::Clone_Proto(L"Vortex_Particle", this, 70));
	m_uMapComponent[ID_STATIC].insert({ L"Vortex_Particle", m_Particle });

	return S_OK;
}

void CVortexBullet::Pop_Initialize()
{
	m_bHit = false;
	m_Particle->Reset();
}

void CVortexBullet::Free(void)
{
	__super::Free();
}

CVortexBullet * CVortexBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVortexBullet*		pInstance = new CVortexBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
