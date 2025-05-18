#include "EnemyBullet.h"

#include "BulletMgr.h"
#include "EffectManager.h"
#include "Player.h"
#include "Effect.h"
#include "Wall.h"
#include "Floor.h"
#include "SoftPyramid.h"

CEnemyBullet::CEnemyBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBullet(pGraphicDev)
{
	Set_ObjTag(L"EnemyBullet");
	m_fSpeed = 40.f;
	m_fLifeSpan = 3.f;
	m_fAge = 0.f;
	m_Damage = 1;
}

CEnemyBullet::~CEnemyBullet()
{
}

void CEnemyBullet::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
	{
		CBulletMgr::GetInstance()->Push(L"EnemyBullet", this);
	}
}

HRESULT CEnemyBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CEnemyBullet::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead())
		return OBJ_RETPOOL;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	__super::Update_GameObject(fTimeDelta);

	m_pTransform->Move_Walk(m_fSpeed * 2.f, fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CEnemyBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CEnemyBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CEnemyBullet::OnCollisionEnter(const Collision * collsion)
{
}

void CEnemyBullet::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);

	_vec3 vPos = collision->intersectBox._max;

	if (pPlayer && collision->OtherCollider == pPlayer->Get_Component(L"BodyCollider", ID_ALL))
	{
		pPlayer->Get_Damaged(m_Damage);
		SetDead();
	}

	CWall* wall = dynamic_cast<CWall*>(collision->OtherGameObject);
	CFloor* floor = dynamic_cast<CFloor*>(collision->OtherGameObject);
	CSoftPyramid* softPyramid = dynamic_cast<CSoftPyramid*>(collision->OtherGameObject);

	if (wall || floor || softPyramid)
		SetDead();
}

void CEnemyBullet::OnCollisionExit(const Collision * collision)
{
}

HRESULT CEnemyBullet::Add_Component()
{
	CAnimation* pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(pAnimation);
	m_uMapComponent[ID_ALL].emplace(L"Animation", pAnimation);

	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"EnemyBullet_Texture", this));
	NULL_CHECK_RETURN(pTexture);
	m_uMapComponent[ID_STATIC].emplace(L"EnemyBullet_Texture", pTexture);
	pAnimation->BindAnimation(ANIM_SHOT, pTexture, 0.1f);
	pAnimation->SelectState(ANIM_SHOT);

	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMYBULLET));
	NULL_CHECK_RETURN(pCollider);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);

	return S_OK;
}

void CEnemyBullet::Free(void)
{
	__super::Free();
}

CEnemyBullet * CEnemyBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEnemyBullet* pInstance = new CEnemyBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}
