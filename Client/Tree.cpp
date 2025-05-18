#include "Tree.h"
#include "Export_Function.h"

CTree::CTree(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMapObj(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CTree::~CTree()
{
}

HRESULT CTree::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->Set_Scale({ 6.f,6.f,1.f });
	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);
	return S_OK;
}

_int CTree::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead())
		return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	//m_pTransform->Rot_Bill(0.01f);

	return OBJ_NOEVENT;
}

void CTree::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTree::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CTree::Add_Component()
{
	CComponent *pComponent;

	pComponent = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComponent });

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Tree_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Tree_Texture", pComponent });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_OBJ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 2.f,5.f,2.f });
	//pCollider->Set_BoundingBox(m_pTransform->Get_Scale() * 4.f);
}



CGameObject * CTree::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTree* pInstance = new CTree(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

