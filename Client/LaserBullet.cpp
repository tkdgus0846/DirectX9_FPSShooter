#include "LaserBullet.h"
#include "BulletMgr.h"
#include "Monster.h"
#include "EffectManager.h"
#include "Player.h"
#include "..\Engine\ParticleMgr.h"
#include "..\Engine\SoundMgr.h"
#include "Wall.h"
#include "SoftPyramid.h"
#include "Floor.h"
CLaserBullet::CLaserBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	Set_ObjTag(L"LaserBullet");
	m_fSpeed = 1000.f;
	m_fLifeSpan = 3.f;
	m_fAge = 0.f;
	m_Damage = 1;
}

CLaserBullet::~CLaserBullet()
{
}

void CLaserBullet::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
	{
		CBulletMgr::GetInstance()->Push(L"LaserBullet", this);
	}
}

HRESULT CLaserBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();
	
	return result;
}

_int CLaserBullet::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead()) return OBJ_RETPOOL;

	_float fRotSpeed = 360.f * 3.f;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	__super::Update_GameObject(fTimeDelta);

	m_pTransform->m_vInfo[INFO_POS] += m_fSpeed * m_pTransform->m_vInfo[INFO_RIGHT] * fTimeDelta;
	m_pTransform->Rot_Pitch(fRotSpeed, fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CLaserBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CLaserBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	_vec3 scale = m_pTransform->Get_Scale();

	__super::Render_GameObject();
}

void CLaserBullet::OnCollisionEnter(const Collision * collsion)
{

}

void CLaserBullet::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);

	CMonster* monster = dynamic_cast<CMonster*>(collision->OtherGameObject);

	if (monster && collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		_vec3 pos = collision->intersectBox._max;

		CEffect* effect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"ExplosionBlue", pos, { 0.7f,0.7f,0.7f }, 0.1f);
		Add_GameObject(effect);

		STOP_PLAY_SOUND(L"sfxShatter.wav", SOUND_EFFECT, 0.5f);

		monster->Get_Damaged(m_Damage);
	}

	CWall* wall = dynamic_cast<CWall*>(collision->OtherGameObject);
	CFloor* floor = dynamic_cast<CFloor*>(collision->OtherGameObject);
	CSoftPyramid* softPyramid = dynamic_cast<CSoftPyramid*>(collision->OtherGameObject);

	if (wall || floor || softPyramid)
	{
		_vec3 pos = collision->intersectBox._max;
		CEffect* effect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"ExplosionBlue", pos, { 1.3f,1.3f,1.0f }, 0.1f);
		STOP_PLAY_SOUND(L"sfxShatter.wav", SOUND_EFFECT, 0.5f);
		Add_GameObject(effect);
		SetDead();
		if (softPyramid != nullptr)
		{
			
			softPyramid->SetDead();
			return;
		}
		
		return;
	}
}

void CLaserBullet::OnCollisionExit(const Collision * collision)
{
}

HRESULT CLaserBullet::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Laser_Blue_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Laser_Blue_Texture", texture });

	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);

	animation->BindAnimation(ANIM_SHOT, texture, 0.05f);
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

void CLaserBullet::Free(void)
{
	__super::Free();
}

CLaserBullet * CLaserBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLaserBullet*		pInstance = new CLaserBullet(pGraphicDev);
	
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}


