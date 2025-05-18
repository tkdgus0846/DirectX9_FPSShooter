#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"

#include "Export_Utility.h"

CCollider::CCollider(LPDIRECT3DDEVICE9 pGraphicDev) :
	CComponent(pGraphicDev),
	m_bEnabled(true),
	m_pMesh(nullptr),
	m_bIsRender(false),
	m_bRenderByOwnerPos(true),
	m_vCenterPos({0.f,0.f,0.f}),
	m_VOriginCenterPos({ 0.f,0.f,0.f })
{
}

CCollider::CCollider(const CCollider & rhs) :
	CComponent(rhs),
	m_bEnabled(rhs.m_bEnabled),
	m_pBoundingBox(rhs.m_pBoundingBox),
	m_pMesh(rhs.m_pMesh),
	m_bIsRender(rhs.m_bIsRender),
	m_bRenderByOwnerPos(rhs.m_bRenderByOwnerPos),
	m_vCenterPos(rhs.m_vCenterPos),
	m_VOriginCenterPos(rhs.m_VOriginCenterPos)
{
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Resource/CollisionDebug/Green.png", (LPDIRECT3DTEXTURE9*)&m_GreenTexture);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Resource/CollisionDebug/Red.png", (LPDIRECT3DTEXTURE9*)&m_RedTexture);
}

CCollider::~CCollider()
{
}

HRESULT CCollider::Ready_Collider()
{
	return S_OK;
}

_int CCollider::Update_Component(const _float& fTimeDelta)
{
	
	_int iExit = __super::Update_Component(fTimeDelta);
	if (iExit != 0) return iExit;

	_vec3 offsetPoint;
	m_pGameObject->m_pTransform->Get_Info(INFO_POS, &offsetPoint);
	
	m_vCenterPos = m_VOriginCenterPos + offsetPoint;
	m_pBoundingBox->Offset(m_vCenterPos);

	for (auto iter = m_CollisionList.begin(); iter != m_CollisionList.end();)
	{
		if (iter->first == nullptr || iter->second.OtherCollider->Get_Enable() == false)
		{
			iter = m_CollisionList.erase(iter);
		}	
		else iter++;
	}

	return 0;
}

void CCollider::LateUpdate_Component()
{
	
}

void CCollider::Render_Component()
{
	if (m_bIsRender == false) return;

	_matrix worldMatrix;
	worldMatrix.Translation(m_vCenterPos.x, m_vCenterPos.y, m_vCenterPos.z);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &worldMatrix);
	

	if (m_CollisionList.empty()) m_pGraphicDev->SetTexture(0, m_GreenTexture);
	else m_pGraphicDev->SetTexture(0, m_RedTexture);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pMesh->DrawSubset(0);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetTexture(0, nullptr);
}

void CCollider::OnCollisionEnter(const Collision * collision)
{
	if (Get_WorldTime() < COLLISON_IGNORE_TIME) return;
	if (m_bEnabled == false) return;
	if (m_pGameObject->GetDead()) return;

	//cout << this << ": OnCollisionEnter!" << " dir: " << collision->CollisionDir << endl;
	m_pGameObject->OnCollisionEnter(collision);
}

void CCollider::OnCollisionStay(const Collision * collision)
{
	if (Get_WorldTime() < COLLISON_IGNORE_TIME) return;
	if (m_bEnabled == false) return;
	if (m_pGameObject->GetDead()) return;

	//cout << this << ": OnCollisionStay!" << " dir: " << collision->CollisionDir << endl;
	m_pGameObject->OnCollisionStay(collision);
}

void CCollider::OnCollisionExit(const Collision * collision)
{
	if (Get_WorldTime() < COLLISON_IGNORE_TIME) return;
	if (m_bEnabled == false) return;
	if (m_pGameObject->GetDead()) return;

	//cout << this << ": OnCollisionExit!" << endl;
	m_pGameObject->OnCollisionExit(collision);
}

// 가로, 세로, 깊이 사이즈 넣어주면 됨.
void CCollider::Set_BoundingBox(const _vec3 & vSize)
{
	if (m_pMesh) Safe_Release(m_pMesh);

	D3DXCreateBox(m_pGraphicDev,
		vSize.x,
		vSize.y,
		vSize.z,
		&m_pMesh, NULL);
	if (nullptr == m_pBoundingBox)
		m_pBoundingBox = new BoundingBox(-vSize / 2, vSize / 2);
	else
	{
		m_pBoundingBox->_offsetMax = vSize / 2;
		m_pBoundingBox->_offsetMin = -vSize / 2;
		/*_vec3 offsetPoint;
		m_pGameObject->m_pTransform->Get_Info(INFO_POS, &offsetPoint);*/
		//m_pBoundingBox->Offset(offsetPoint);
	}
}

void CCollider::Set_BoundingBox(const _vec3& vSize, const _vec3& vCenterPos)
{
	if (m_pMesh) Safe_Release(m_pMesh);

	D3DXCreateBox(m_pGraphicDev,
		vSize.x,
		vSize.y,
		vSize.z,
		&m_pMesh, NULL);
	if (nullptr == m_pBoundingBox)
	{
		m_pBoundingBox = new BoundingBox(-vSize / 2, vSize / 2);
		//m_pBoundingBox->Offset(vCenterPos);
	}
	else
	{
		m_pBoundingBox->_offsetMax = vSize / 2;
		m_pBoundingBox->_offsetMin = -vSize / 2;
		//m_pBoundingBox->Offset(vCenterPos);	
	}

	m_VOriginCenterPos = vCenterPos;
}

CCollider * CCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCollider* pInstance = new CCollider(pGraphicDev);

	if (FAILED(pInstance->Ready_Collider()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CCollider::Clone(void)
{
	CCollider* pClone = new CCollider(*this);
	return pClone;
}

void CCollider::Free(void)
{
	/*if (m_bClone == true)
	{
		Engine::Remove_Collider(this, m_eColGroup);
	}*/

	// 콜라이더가 삭제될때 나랑 충돌하고있던놈들로 가서 나를 빼주는거죠
	for (auto OtherCollider : m_CollisionList)
	{
		for (auto& iter : OtherCollider.first->m_CollisionList)
		{
			if (iter.first == this)
			{
				OtherCollider.first->m_CollisionList.erase(this);
				break;
			}
		}	
	}
	
	m_CollisionList.clear();
	Safe_Delete(m_pBoundingBox);
	Safe_Release(m_pMesh);
	Safe_Release(m_GreenTexture);
	Safe_Release(m_RedTexture);

	__super::Free();
}
