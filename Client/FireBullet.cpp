#include "FireBullet.h"
#include "BulletMgr.h"
#include "Monster.h"
#include "EffectManager.h"
#include "Player.h"
#include "..\Engine\ParticleMgr.h"
#include "..\Engine\SoundMgr.h"

CFireBullet::CFireBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	Set_ObjTag(L"FireBullet");
	m_fSpeed = 6.f;
	m_fLifeSpan = 1.f;
	m_fAge = 0.f;
	m_Damage = 1;
}

CFireBullet::~CFireBullet()
{
}

void CFireBullet::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
		CBulletMgr::GetInstance()->Push(L"FireBullet", this);
}

HRESULT CFireBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CFireBullet::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead()) return OBJ_RETPOOL;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	__super::Update_GameObject(fTimeDelta);

	m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);
	Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CFireBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();

}

void CFireBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	_vec3 scale = m_pTransform->Get_Scale();

	__super::Render_GameObject();
}

void CFireBullet::OnCollisionEnter(const Collision * collsion)
{
	CMonster* monster = dynamic_cast<CMonster*>(collsion->OtherGameObject);

	if (monster && collsion->OtherCollider == collsion->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		_vec3 pos = collsion->intersectBox._max;
		CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"UpSmoke_Particle", 1, pos, {0.f,1.f,0.f});
		/*CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"JumpSmoke_Particle", 100, pos, {0.f,0.f,0.f});*/

		STOP_PLAY_SOUND(L"sfxSplode.wav", SOUND_EFFECT, 1.0f);
		
		Add_GameObject(particle);
		monster->Get_Damaged(m_Damage);
	}
}

void CFireBullet::OnCollisionStay(const Collision * collision)
{
	//__super::OnCollisionStay(collision);

	
}

void CFireBullet::OnCollisionExit(const Collision * collision)
{
}

HRESULT CFireBullet::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FireBullet_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FireBullet_Texture", texture });

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

void CFireBullet::Free(void)
{
	__super::Free();
}

CFireBullet * CFireBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFireBullet*		pInstance = new CFireBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
