#include "Portal.h"
#include "Export_Function.h"
#include "Player.h"

CPortal::CPortal(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{
	Set_ObjTag(Tag());
	Set_LayerID(LAYER_TENNEL);

	//m_pTransform->Set_MoveType(CTransform::AIRCRAFT);
}

CPortal::~CPortal()
{
}

HRESULT CPortal::Ready_GameObject(void)
{
	HRESULT Result = __super::Ready_GameObject();

	m_pTransform->m_vScale = { 5.f, 5.f, 5.f };
	//m_pTransform->Rot_Pitch(90.f, 1.f);

	return Result;
}

_int CPortal::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) 
		return OBJ_DEAD;

	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	//m_pTransform->Rot_Roll(-360.f, fTimeDelta*1.5f);

	return __super::Update_GameObject(fTimeDelta);
}

void CPortal::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CPortal::Render_GameObject(void)
{
	__super::Render_GameObject();
}

HRESULT CPortal::Add_Component()
{
	CComponent* pComp = nullptr;

	pComp = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pComp, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComp });

	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Portal_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Portal_Texture", pTexture });

	CAnimation* pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Animation", pAnimation });

	pAnimation->BindAnimation(ANIM_IDLE, pTexture, 0.35f);
	pAnimation->SelectState(ANIM_IDLE);


	CCollider*	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });

	m_pTransform->Set_Scale({ 1.f, 1.f, 1.f });
	pCollider->Set_BoundingBox({ 2.f,2.f,2.f });

	return S_OK;
}

void CPortal::OnCollisionEnter(const Collision * collsion)
{
}

CPortal * CPortal::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CPortal*		pInstance = new CPortal(pGraphicDev);

	pInstance->Set_Pos(vPos);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPortal::OnCollisionStay(const class Collision* collision)
{
	if (dynamic_cast<CPlayer*>(collision->OtherGameObject))
	{
		CManagement::GetInstance()->Next_Stage();
		SetDead();
		return;
	}
}

void CPortal::Free(void)
{
	__super::Free();
}
