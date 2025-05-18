#include "stdafx.h"
#include "Floor.h"

#include "WormHead.h"
#include "WormBody.h"
#include "WormTail.h"
#include "Export_Function.h"
#include "BossHp.h"
#include "Creature.h"

CFloor::CFloor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_ENVIRONMENT);
	Set_ObjTag(L"Floor");
}

CFloor::~CFloor()
{
}

HRESULT CFloor::Ready_GameObject(STAGEINFO stageInfo)
{
	switch (stageInfo)
	{
	case STAGE1:
		m_FloorTextureName = L"FloorSmall";
		break;
	case STAGE2:
		m_FloorTextureName = L"FloorSmall #421572";
		break;
	case STAGE3:
		m_FloorTextureName = L"FloorSmall #421723";
		break;
	case STAGE4:
		m_FloorTextureName = L"FloorSmall #421201";
		break;
	default:
		break;
	}

	HRESULT result = __super::Ready_GameObject(); // ������Ʈ �߰����ִ��۾�

	return result;
}

_int CFloor::Update_GameObject(const _float& fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	__super::Update_GameObject(fTimeDelta);
	
	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CFloor::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CFloor::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CFloor::OnCollisionEnter(const Collision * collsion)
{
}

void CFloor::OnCollisionStay(const Collision * collision)
{

	/*if (Get_WorldTime() < COLLISON_IGNORE_TIME) return;*/
	
	if (dynamic_cast<CWormHead*>(collision->OtherGameObject) ||
		dynamic_cast<CWormBody*>(collision->OtherGameObject) ||
		dynamic_cast<CWormTail*>(collision->OtherGameObject))
		return;

	CCreature* creature = dynamic_cast<CCreature*>(collision->OtherGameObject);
	if (creature == nullptr) return;

	if (collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		_float height = collision->amountVec.y;
		creature->m_pTransform->m_vInfo[INFO_POS].y += height;
	}
}

void CFloor::OnCollisionExit(const Collision * collision)
{
}

void CFloor::SetTextureName(const _tchar* name)
{
	m_FloorTextureName = name;
}

HRESULT CFloor::Add_Component(void)
{
	CComponent* pComp;
	pComp = dynamic_cast<CFloorTex*>(Engine::Clone_Proto(L"FloorTex",this));
	NULL_CHECK_RETURN(pComp, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"FloorTex", pComp });

	pComp = dynamic_cast<CTexture*>(Engine::Clone_Proto(m_FloorTextureName,this));
	NULL_CHECK_RETURN(pComp, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ m_FloorTextureName, pComp });

	CCollider*	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });

	m_pTransform->Set_Scale({ 1.f, 1.f, 1.f });
	pCollider->Set_BoundingBox({ 50.f,10.f,50.f }, { 25.f,-5.f,25.f });

	return S_OK;
}

CFloor* CFloor::Create(LPDIRECT3DDEVICE9 pGraphicDev, STAGEINFO stageInfo)
{
	CFloor*		pInstance = new CFloor(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(stageInfo)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CFloor::Free(void)
{
	__super::Free();
}