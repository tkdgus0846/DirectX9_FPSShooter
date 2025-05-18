#include "RootAttack.h"

#include "Player.h"
#include "BulletMgr.h"
#include "Export_Function.h"

CRootAttack::CRootAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBullet(pGraphicDev)
{
	Set_ObjTag(L"RootAttack");
	m_fSpeed = 13.f;
	m_fLifeSpan = 7.f;
	m_fAge = 0.f;
	m_Damage = 1;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);
}

CRootAttack::~CRootAttack()
{
}

void CRootAttack::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
	{
		CBulletMgr::GetInstance()->Push(L"RootAttack", this);
	}
}

HRESULT CRootAttack::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CRootAttack::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead())
		return OBJ_RETPOOL;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	__super::Update_GameObject(fTimeDelta);

	m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CRootAttack::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CRootAttack::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CRootAttack::OnCollisionEnter(const Collision * collsion)
{
}

void CRootAttack::OnCollisionStay(const Collision * collision)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);

	if (pPlayer && collision->OtherCollider == pPlayer->Get_Component(L"BodyCollider", ID_ALL))
	{
		pPlayer->Get_Damaged(m_Damage);
		SetDead(true);
	}
}

void CRootAttack::OnCollisionExit(const Collision * collision)
{
}

HRESULT CRootAttack::Add_Component()
{
	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });
	animation->SelectState(ANIM_SHOT);

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"RootAttack", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"RootAttack", texture });
	animation->BindAnimation(ANIM_SHOT, texture, 0.1f);

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMYBULLET));
	pCollider->Set_BoundingBox({ 1.f, 1.f, 1.f });
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });

	return S_OK;
}

void CRootAttack::Free(void)
{
	__super::Free();
}

CRootAttack * CRootAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRootAttack* pInstance = new CRootAttack(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
