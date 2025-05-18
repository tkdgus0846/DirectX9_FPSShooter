#include "stdafx.h"
#include "NormalBullet.h"

#include "Export_Function.h"
#include "BulletMgr.h"
#include "Turret.h"
#include "EffectManager.h"
#include "Player.h"
#include "ParticleMgr.h"
#include "..\Engine\ColorParticle.h"
#include "Wall.h"
#include "..\Engine\SoundMgr.h"
#include "Floor.h"
#include "SoftPyramid.h"

CNormalBullet::CNormalBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	Set_ObjTag(L"NormalBullet");
	m_fSpeed = 50.f;
	m_fLifeSpan = 3.f;
	m_fAge = 0.f;
	m_Damage = 1;
}

CNormalBullet::~CNormalBullet()
{
}

void CNormalBullet::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
	{
		CBulletMgr::GetInstance()->Push(L"NormalBullet", this);
	}
}

HRESULT CNormalBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CNormalBullet::Update_GameObject(const _float& fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead()) 
		return OBJ_RETPOOL;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	__super::Update_GameObject(fTimeDelta);

	m_pTransform->Move_Walk(m_fSpeed*2.f, fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA, this);
	
	return OBJ_NOEVENT;
}

void CNormalBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CNormalBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CNormalBullet::OnCollisionEnter(const Collision* collsion)
{
}

void CNormalBullet::OnCollisionStay(const Collision* collision)
{
	__super::OnCollisionStay(collision);

	CMonster* monster = dynamic_cast<CMonster*>(collision->OtherGameObject);

	if (monster && collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		_vec3 pos = collision->intersectBox._max;

		/*CEffect* effect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"RedBlood", pos, { 0.7f,0.7f,0.7f }, 0.1f);
		Add_GameObject(effect);*/

		monster->Get_Damaged(m_Damage);
		SetDead();

		CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"NormalBullet_Particle", 4, pos);
		
		STOP_PLAY_SOUND(L"sfxHurt.wav", SOUND_EFFECT, 1.f);
		Add_GameObject(particle);
		return;
	}

	CWall* wall = dynamic_cast<CWall*>(collision->OtherGameObject);
	CFloor* floor = dynamic_cast<CFloor*>(collision->OtherGameObject);
	CSoftPyramid* softPyramid = dynamic_cast<CSoftPyramid*>(collision->OtherGameObject);
	
	if (wall || floor || softPyramid)
	{
		
		_vec3 pos = collision->intersectBox._max;
		SetDead();
		//if (softPyramid != nullptr)
		//{
		//	CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"PyramidDestory_Particle", 30, pos);
		//	Add_GameObject(particle);
		//	//softPyramid->SetDead();
		//	return;
		//}
		CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"NormalBullet_Particle", 4, pos);
		STOP_PLAY_SOUND(L"sfxHurt.wav", SOUND_ENVIRONMENT, 1.f);
		Add_GameObject(particle);
		return;
	}
}

void CNormalBullet::OnCollisionExit(const Collision* collision)
{
}

HRESULT CNormalBullet::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"NormalBullet_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"NormalBullet_Texture", texture });

	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);

	animation->BindAnimation(ANIM_SHOT, texture, 0.1f);
	animation->SelectState(ANIM_SHOT);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_PLAYERBULLET));
	pCollider->Set_BoundingBox({ 0.5f, 0.5f, 0.5f });
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });

	return S_OK;
}

void CNormalBullet::Pop_Initialize()
{
	m_bHit = false;
}

void CNormalBullet::Free(void)
{
	__super::Free();
}

CNormalBullet* CNormalBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNormalBullet*		pInstance = new CNormalBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
