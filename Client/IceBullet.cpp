#include "IceBullet.h"
#include "BulletMgr.h"
#include "Monster.h"
#include "EffectManager.h"
#include "Wall.h"
#include "..\Engine\SoundMgr.h"
#include "Floor.h"

CIceBullet::CIceBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	Set_ObjTag(L"IceBullet");
	m_fSpeed = 20.f;
	m_fLifeSpan = 5.f;
	m_fAge = 0.f;
	m_Damage = 5;
}

CIceBullet::~CIceBullet()
{
}

void CIceBullet::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
		CBulletMgr::GetInstance()->Push(L"IceBullet", this);
}

HRESULT CIceBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CIceBullet::Update_GameObject(const _float & fTimeDelta)
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

void CIceBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CIceBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CIceBullet::OnCollisionEnter(const Collision * collsion)
{
}

void CIceBullet::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);

	CMonster* monster = dynamic_cast<CMonster*>(collision->OtherGameObject);

	if (monster && collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		_vec3 pos = collision->intersectBox._max;
		CEffect* effect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"ExplosionBlue", pos, { 1.3f,1.3f,1.0f }, 0.1f);
		Add_GameObject(effect);
		monster->Get_Damaged(m_Damage);
		STOP_PLAY_SOUND(L"sfxShatter.wav", SOUND_EFFECT, 0.6f);
		SetDead();
	}

	CWall* wall = dynamic_cast<CWall*>(collision->OtherGameObject);
	CFloor* floor = dynamic_cast<CFloor*>(collision->OtherGameObject);

	if (wall || floor)
	{
		_vec3 pos = collision->intersectBox._max;
		SetDead();
		CEffect* effect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"ExplosionBlue", pos, { 1.3f,1.3f,1.0f }, 0.1f);
		STOP_PLAY_SOUND(L"sfxShatter.wav", SOUND_ENVIRONMENT, 0.6f);
		Add_GameObject(effect);
		return;
	}
}

void CIceBullet::OnCollisionExit(const Collision * collision)
{
}

HRESULT CIceBullet::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"IceBullet_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"IceBullet_Texture", texture });

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

void CIceBullet::Free(void)
{
	__super::Free();
}

CIceBullet * CIceBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIceBullet*		pInstance = new CIceBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
