#include "OnlyCollisionObj.h"
#include "Export_Function.h"


COnlyCollisionObj::COnlyCollisionObj(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMapObj(pGraphicDev)
{
	
}

COnlyCollisionObj::~COnlyCollisionObj()
{
}

HRESULT COnlyCollisionObj::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();
	SetDead(false);
	return result;
}

_int COnlyCollisionObj::Update_GameObject(const _float & fTimeDelta)
{
	
	__super::Update_GameObject(fTimeDelta);

	Add_RenderGroup(RENDER_NONALPHA, this);
	return OBJ_NOEVENT;
}

void COnlyCollisionObj::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void COnlyCollisionObj::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

COnlyCollisionObj * COnlyCollisionObj::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, _vec3 ColSize)
{
	COnlyCollisionObj*		pInstance = new COnlyCollisionObj(pGraphicDev);
	pInstance->Set_ColSize(ColSize);
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	pInstance->m_pTransform->m_vInfo[INFO_POS] = vPos;
	return pInstance;
}

void COnlyCollisionObj::OnCollisionEnter(const Collision * collsion)
{
}

void COnlyCollisionObj::OnCollisionStay(const Collision * collision)
{
}

void COnlyCollisionObj::OnCollisionExit(const Collision * collision)
{
}

HRESULT COnlyCollisionObj::Add_Component()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex",this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"RcTex", pBufferCom });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ m_vColSize.x, m_vColSize.y, m_vColSize.z });

	return S_OK;
}
