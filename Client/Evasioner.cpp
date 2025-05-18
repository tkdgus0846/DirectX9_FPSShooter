#include "Evasioner.h"

#include "Bullet.h"
#include "Export_Function.h"

CEvasioner::CEvasioner(LPDIRECT3DDEVICE9 pGraphicDev)
	:CEnemy(pGraphicDev),
	m_bInHole(false)
{
	Set_ObjTag(Tag());
}

CEvasioner::~CEvasioner()
{
}

HRESULT CEvasioner::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 10.f;
	m_iHp = 1;
	m_pTransform->m_vScale = { 1.5f, 1.5f, 1.5f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);
	
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CEvasioner::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) 
		return OBJ_DEAD;

	if (m_bInHole == false)
		m_pTransform->m_vInfo[INFO_POS].y = 1.5f;

	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CEvasioner::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CEvasioner::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CEvasioner::OnCollisionStay(const Collision * collision)
{
	if(dynamic_cast<CBullet*>(collision->OtherGameObject))
		m_pAnimation->SelectState(ANIM_WALK);
}

void CEvasioner::OnCollisionExit(const Collision * collision)
{
	m_pAnimation->SelectState(ANIM_IDLE);
}

HRESULT CEvasioner::Add_Component()
{
	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAnimation });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Evasioner_Idle_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Evasioner_Idle_Texture", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture, 0.3f);
	m_pAnimation->SelectState(ANIM_IDLE);

	texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Evasioner_Evasion_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Evasioner_Evasion_Texture", texture });
	m_pAnimation->BindAnimation(ANIM_WALK, texture, 0.3f);

	texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Evasioner_Dead_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Evasioner_Dead_Texture", texture });
	m_pAnimation->BindAnimation(ANIM_DEAD, texture, 0.3f);

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"EvasBullet", this, COL_OBJ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"EvasBullet", pCollider });
	pCollider->Set_BoundingBox({ 8.f, 8.f, 8.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"HoleCollider", this, COL_OBJ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"HoleCollider", pCollider });
	pCollider->Set_BoundingBox({ 3.f, 2.f, 3.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_EvasionAndAttack(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CEvasioner * CEvasioner::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CEvasioner* pInstance = new CEvasioner(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CEvasioner::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEvasioner* pInstance = new CEvasioner(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3())))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CEvasioner::Free(void)
{
	__super::Free();
}
