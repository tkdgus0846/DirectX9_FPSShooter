#include "SnowMan.h"
#include "Export_Function.h"


CSnowMan::CSnowMan(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMapObj(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CSnowMan::~CSnowMan()
{
}

HRESULT CSnowMan::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->Set_Scale({ 3.f,3.f,1.f });
	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);
	return S_OK;
}

_int CSnowMan::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead())
		return OBJ_DEAD;

	__super::Update_GameObject(fTimeDelta);
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CSnowMan::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CSnowMan::Add_Component()
{
	CComponent *pComponent;
	pComponent = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComponent });

	CTexture* pTex = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SnowMan", this));
	NULL_CHECK_RETURN(pTex, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SnowMan", pTex });

	CAnimation* pAni = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation"
		, this));
	NULL_CHECK_RETURN(pAni, E_FAIL);
	pAni->BindAnimation(ANIM_IDLE, pTex);
	m_uMapComponent[ID_ALL].insert({ L"Animation", pAni });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_OBJ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox(m_pTransform->Get_Scale() * 4.f);

	return S_OK;
}

CGameObject * CSnowMan::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSnowMan* pInstance = new CSnowMan(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSnowMan::OnCollisionStay(const Collision * collision)
{
}
