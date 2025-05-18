#include "stdafx.h"
#include "RandomLook.h"

#include "Export_Utility.h"

CRandomLook::CRandomLook(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_bIsAircraft(true)
{
}

CRandomLook::CRandomLook(const CRandomLook & rhs)
	: CBehavior(rhs), m_bIsAircraft(rhs.m_bIsAircraft)
{
}

CRandomLook::~CRandomLook()
{
}

HRESULT CRandomLook::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CRandomLook::Update_Component(const _float & fTimeDelta)
{
	_vec3 vRandomLook;
	_vec3 vMin(-180.f, 0.f, -180.f);
	_vec3 vMax(180.f, 0.f, 180.f);

	if (m_bIsAircraft)
	{
		vMin = { -10.f, -210.f, -10.f };
		vMax = { 10.f, -110.f, 10.f };
	}

	GetRandomVector(&vRandomLook, &vMin, &vMax);
	vRandomLook.Normalize();

	if (m_bIsAircraft)
		m_pGameObject->m_pTransform->Set_Dir(vRandomLook);
	else
		m_pGameObject->m_pTransform->Set_Dir(_vec3(vRandomLook.x, vRandomLook.y, vRandomLook.z));

	return BEHAVIOR_SUCCES;
}

void CRandomLook::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CRandomLook::Render_Component(void)
{
	__super::Render_Component();
}

CRandomLook * CRandomLook::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRandomLook* pInstance = new CRandomLook(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CRandomLook::Clone(void)
{
	return new CRandomLook(*this);
}

void CRandomLook::Free()
{
	__super::Free();
}
