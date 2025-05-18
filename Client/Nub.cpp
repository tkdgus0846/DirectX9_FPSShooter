#include "Nub.h"

#include "Export_Function.h"

CNub::CNub(LPDIRECT3DDEVICE9 pGraphicDev)
	:CEnemy(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CNub::~CNub()
{
}

HRESULT CNub::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 10.f;
	m_iAttack = 1;
	m_iHp = 1;

	m_pTransform->m_vScale = { 0.5f, 0.5f, 0.5f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CNub::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead())
		return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CNub::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CNub::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

HRESULT CNub::Add_Component()
{
	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });
	animation->SelectState(ANIM_WALK);

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Nub_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Nub_Texture", texture });
	animation->BindAnimation(ANIM_WALK, texture, 0.3f);

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 1.f, 1.f, 1.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 70.f, 10.f, 70.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_PatrolAndFollow_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CNub * CNub::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CNub* pInstance = new CNub(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CNub::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNub* pInstance = new CNub(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3())))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CNub::Free(void)
{
	__super::Free();
}
