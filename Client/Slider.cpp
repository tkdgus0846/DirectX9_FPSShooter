#include "Slider.h"
#include "Export_Function.h"
#include "Wall.h"
#include "Player.h"

CSlider::CSlider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMapObj(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CSlider::~CSlider()
{
}

HRESULT CSlider::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);
	
	return S_OK;
}

_int CSlider::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead())
		return OBJ_DEAD;

	__super::Update_GameObject(fTimeDelta);
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

//#ifdef _IMGUI
//	// IMGUI에서는 랜더그룹에만 넣어주고 움직임 로직을 막음.
//	return OBJ_NOEVENT;
//#endif

	_matrix viewMat;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMat);
	//m_pTransform->Set_Billboard(&viewMat);

	m_pTransform->Move_Walk(19.f, fTimeDelta);
	return OBJ_NOEVENT;
}

void CSlider::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSlider::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CSlider::Add_Component()
{
	CComponent *pComponent;

	pComponent = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComponent });

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Slider_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Slider_Texture", pComponent });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_OBJ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox(m_pTransform->Get_Scale() * 4.f);

	return S_OK;
}

void CSlider::OnCollisionEnter(const Collision * collsion)
{
	if (dynamic_cast<CWall*>(collsion->OtherGameObject))
	{
		m_pTransform->Reverse_Dir();
	}

	if (CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject))
	{
		pPlayer->Get_Damaged(1.f);
	}
}

CGameObject * CSlider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSlider* pInstance = new CSlider(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSlider::Free(void)
{
	__super::Free();
}
