#include "SnowTree.h"
#include "Export_Function.h"


CSnowTree::CSnowTree(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMapObj(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CSnowTree::~CSnowTree()
{
}

HRESULT CSnowTree::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->Set_Scale({ 5.f, 6.f,1.f });
	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);

	return S_OK;
}

_int CSnowTree::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead())
		return OBJ_DEAD;

	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CSnowTree::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CSnowTree::Add_Component()
{
	CComponent *pComponent;
	pComponent = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComponent });

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SnowTree", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"SnowTree", pComponent });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_OBJ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox(m_pTransform->Get_Scale() * 4.f);

	return S_OK;
}

CGameObject * CSnowTree::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSnowTree* pInstance = new CSnowTree(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSnowTree::OnCollisionStay(const Collision * collision)
{
}
