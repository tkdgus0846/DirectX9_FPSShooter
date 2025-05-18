#include "Guppi.h"

#include "Export_Function.h"

CGuppi::CGuppi(LPDIRECT3DDEVICE9 pGraphicDev)
	:CEnemy(pGraphicDev), m_bIsDamaged(false)
{
	Set_ObjTag(Tag());
}

CGuppi::~CGuppi()
{
}

HRESULT CGuppi::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 10.f;
	m_iAttack = 1;
	m_iHp = 6;
	m_iMaxHp = 6;

	m_pTransform->m_vScale = { 1.5f, 1.5f, 1.5f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.001f);

	Get_BlackBoard()->Add_Type(L"bIsDamaged", m_bIsDamaged);
	return result;
}

_int CGuppi::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead())
		return OBJ_DEAD;

	if (false == m_bIsDamaged && m_iHp < m_iMaxHp)
	{
		dynamic_cast<CCollider*>(Get_Component(L"BodyCollider", ID_ALL))->Set_BoundingBox(_vec3(3.f, 3.f, 3.f));
		m_bIsDamaged = true;
		Get_BlackBoard()->Set_Type(L"bIsDamaged", m_bIsDamaged);
	}

	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CGuppi::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CGuppi::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

HRESULT CGuppi::Add_Component()
{
	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });
	animation->SelectState(ANIM_WALK);

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Guppi_Blue_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Guppi_Blue_Texture", texture });
	animation->BindAnimation(ANIM_WALK, texture, 0.3f);

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 3.f, 2.3f, 3.f }, { 0.f, 0.7f, 0.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 70.f, 10.f, 70.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_JumpFollowAI(0.6f, true, L"bIsDamaged"), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CGuppi * CGuppi::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CGuppi* pInstance = new CGuppi(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CGuppi::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGuppi* pInstance = new CGuppi(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3())))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CGuppi::Free(void)
{
	__super::Free();
}
