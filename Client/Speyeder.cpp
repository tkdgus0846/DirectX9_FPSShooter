#include "Speyeder.h"

#include "Player.h"
#include "Export_Function.h"

CSpeyeder::CSpeyeder(LPDIRECT3DDEVICE9 pGraphicDev)
	:CEnemy(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CSpeyeder::~CSpeyeder()
{
}

HRESULT CSpeyeder::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 10.f;
	m_iAttack = 2;
	m_iHp = 2;

	m_pTransform->m_vScale = { 0.7f, 0.7f, 0.7f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->m_vInfo[INFO_POS].y += 2.f;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CSpeyeder::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) 
		return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CSpeyeder::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSpeyeder::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CSpeyeder::OnCollisionStay(const Collision * collision)
{
	if (collision->MyCollider == Get_Component(L"BodyCollider", ID_ALL) && dynamic_cast<CPlayer*>(collision->OtherGameObject))
	{
		if (m_fCurTime - m_fPreTime > 2.f)
			m_fPreTime = Get_WorldTime();

		m_fCurTime = Get_WorldTime();

		__super::OnCollisionStay(collision);
		m_pAnimation->SelectState(ANIM_ATTACK);
		m_fSpeed = 0.f;

		if (m_fCurTime - m_fPreTime > 0.8f)
		{
			m_pColExplosion->Set_Enable(true);
			SetDead(true);
		}
	}
}

HRESULT CSpeyeder::Add_Component()
{
	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAnimation });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Speyeder_Walk_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Speyeder_Walk_Texture", texture });
	m_pAnimation->BindAnimation(ANIM_WALK, texture, 0.3f);
	m_pAnimation->SelectState(ANIM_WALK);

	texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Speyeder_Stay_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Speyeder_Stay_Texture", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture, 0.1f);

	texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Speyeder_Jump_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Speyeder_Jump_Texture", texture });
	m_pAnimation->BindAnimation(ANIM_JUMP, texture, 0.5f);

	texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Speyeder_Explosion_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Speyeder_Explosion_Texture", texture });
	m_pAnimation->BindAnimation(ANIM_ATTACK, texture, 0.5f);

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 1.4f, 1.4f, 1.4f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 50.f, 10.f, 50.f });

	m_pColExplosion = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Explosion", this, COL_EXPLOSION));
	NULL_CHECK_RETURN(m_pColExplosion, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Explosion", m_pColExplosion);
	m_pColExplosion->Set_BoundingBox({ 3.f, 3.f, 3.f });
	m_pColExplosion->Set_Enable(false);

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_PAF_LeapJumpAI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CSpeyeder * CSpeyeder::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CSpeyeder* pInstance = new CSpeyeder(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CSpeyeder::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSpeyeder* pInstance = new CSpeyeder(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3{})))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSpeyeder::Free(void)
{
	__super::Free();
}
