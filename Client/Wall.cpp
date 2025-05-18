#include "stdafx.h"
#include "Wall.h"

#include "WormHead.h"
#include "WormBody.h"
#include "WormTail.h"
#include "Evasioner.h"
#include "Export_Function.h"

CWall::CWall(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_ENVIRONMENT);
	Set_ObjTag(L"Wall");

}

CWall::~CWall()
{
}

void CWall::OnCollisionEnter(const Collision* collision)
{
	
}

void CWall::OnCollisionStay(const Collision* collision)
{
	if (dynamic_cast<CWormHead*>(collision->OtherGameObject) ||
		dynamic_cast<CWormBody*>(collision->OtherGameObject) ||
		dynamic_cast<CWormTail*>(collision->OtherGameObject))
		return;

	/*if (Get_WorldTime() < COLLISON_IGNORE_TIME)
		return;*/

	if ((collision->MyCollider == Get_Component(L"Collider", ID_ALL) && 
		collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL)) ||
		(collision->MyCollider == Get_Component(L"Collider", ID_ALL) &&
		dynamic_cast<CEvasioner*>(collision->OtherGameObject)))
	{		
		_vec3 amountVec = collision->amountVec;
		if (m_pTransform == nullptr) return;

		_float fps60 = Engine::Get_Timer(L"Timer_FPS60");
		const float amount = 20.f;
		switch (collision->CollisionDir)
		{
			/*case DIR_UP:
			m_pTransform->m_vInfo[INFO_POS].y -= amountVec.y;
			break;
			case DIR_DOWN:
			m_pTransform->m_vInfo[INFO_POS].y += amountVec.y;
			break;*/
		case DIR_LEFT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].x -= fps60 * amountVec.x * amount;
			break;
		case DIR_RIGHT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].x += fps60 * amountVec.x * amount;
			break;
		case DIR_FRONT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].z += fps60 * amountVec.z * amount;
			break;
		case DIR_BACK:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].z -= fps60 * amountVec.z * amount;
			break;
		default:
			break;
		}

	}
}

void CWall::OnCollisionExit(const Collision* collision)
{
}

HRESULT CWall::Ready_GameObject(STAGEINFO stageInfo)
{

	switch (stageInfo)
	{
	case STAGE1:
		m_WallTextureName = L"WallPanels";
		break;
	case STAGE2:
		m_WallTextureName = L"WallPanels #420377";
		break;
	case STAGE3:
		m_WallTextureName = L"WallPanels #420744";
		break;
	case STAGE4:
		m_WallTextureName = L"WallPanels #420595";
		break;
	default:
		break;
	}
	
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CWall::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	__super::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CWall::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CWall::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

HRESULT CWall::Add_Component()
{
	CWallTex* pBufferCom = dynamic_cast<CWallTex*>(Engine::Clone_Proto(L"WallTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"WallTex", pBufferCom });

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(m_WallTextureName, this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ m_WallTextureName, m_pTextureCom });


	// Wall이랑 Floor 룸의 콜라이더 리스트에 넣어줘야함.
	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	return S_OK;
}

CWall * CWall::Create(LPDIRECT3DDEVICE9 pGraphicDev, STAGEINFO stageInfo)
{
	CWall*		pInstance = new CWall(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(stageInfo)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CWall::Free(void)
{
	__super::Free();
}
