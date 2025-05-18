#include "stdafx.h"
#include "PickingSphere.h"
#include "Export_Function.h"

CPickingSphere::CPickingSphere(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
	, m_bIsRender(true)
	, m_pMesh(nullptr)
	, m_vOffsetPoint(_vec3())
{
	ZeroMemory(&m_pBoundingSphere, sizeof(BoundingSphere));
}

CPickingSphere::CPickingSphere(const CPickingSphere & rhs)
	: CComponent(rhs)
	, m_bIsRender(rhs.m_bIsRender)
	, m_vOffsetPoint(rhs.m_vOffsetPoint)
{
	Set_PickingSphere(1.f);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Resource/CollisionDebug/Blue.png", (LPDIRECT3DTEXTURE9*)&m_BlueTexture);
}

CPickingSphere::~CPickingSphere()
{
}

HRESULT CPickingSphere::Ready_PickingSphere()
{
	return S_OK;
}

_int CPickingSphere::Update_Component(const _float & fTimeDelta)
{
	m_pGameObject->m_pTransform->Get_Info(INFO_POS, &m_vOffsetPoint);
	m_pBoundingSphere->Offset(m_vOffsetPoint);

	return _int();
}

void CPickingSphere::Render_Component()
{
	if (m_bIsRender == false) return;

	m_pGameObject->m_pTransform->Get_Info(INFO_POS, &m_vOffsetPoint);
	
	_matrix worldMatrix;
	worldMatrix.Translation(m_vOffsetPoint.x, m_vOffsetPoint.y, m_vOffsetPoint.z);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &worldMatrix);

	m_pGraphicDev->SetTexture(0, m_BlueTexture);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pMesh->DrawSubset(0);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetTexture(0, nullptr);
}

void CPickingSphere::Set_PickingSphere(float fSize)
{
	D3DXCreateSphere(m_pGraphicDev
		, fSize
		, 20
		, 20
		, &m_pMesh, nullptr);
	if(nullptr == m_pBoundingSphere)
		m_pBoundingSphere = new BoundingSphere(fSize);
	else
	{
		m_pBoundingSphere->fRadius = fSize;
		m_pGameObject->m_pTransform->Get_Info(INFO_POS, &m_vOffsetPoint);
		m_pBoundingSphere->Offset(m_vOffsetPoint);
	}
}

CPickingSphere* CPickingSphere::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPickingSphere *	pInstance = new	CPickingSphere(pGraphicDev);

	if (FAILED(pInstance->Ready_PickingSphere()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CPickingSphere * CPickingSphere::Clone(void)
{
	return new CPickingSphere(*this);	
}

void CPickingSphere::Free(void)
{
	Safe_Delete(m_pBoundingSphere);
	Safe_Release(m_pMesh);
	Safe_Release(m_BlueTexture);
	__super::Free();
}