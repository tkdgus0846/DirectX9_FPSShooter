#include "TimeInLimit.h"

#include "Export_Function.h"

CTimeInLimit::CTimeInLimit(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_bIsCall(false)
{
}

CTimeInLimit::CTimeInLimit(const CTimeInLimit & rhs)
	: CBehavior(rhs), m_bIsCall(rhs.m_bIsCall)
{
}

CTimeInLimit::~CTimeInLimit()
{
}

HRESULT CTimeInLimit::Ready_Behavior()
{
	m_fCurTime = Get_WorldTime();
	m_fPreTime = Get_WorldTime();

	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CTimeInLimit::Update_Component(const _float & fTimeDelta)
{
	if (m_bIsCall)
		m_fCurTime = Get_WorldTime();
	else
	{
		m_bIsCall = true;
		m_fPreTime = Get_WorldTime();
		return BEHAVIOR_SUCCES;
	}

	if (m_fCurTime - m_fPreTime > m_fTimer)
	{
		m_fPreTime = m_fCurTime;
		m_bIsCall = false;
		return BEHAVIOR_FAIL;
	}

	return BEHAVIOR_SUCCES;
}

void CTimeInLimit::LateUpdate_Component(void)
{
}

void CTimeInLimit::Render_Component(void)
{
}

CTimeInLimit * CTimeInLimit::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTimeInLimit* pInstance = new CTimeInLimit(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CTimeInLimit::Clone(void)
{
	return new CTimeInLimit(*this);
}

void CTimeInLimit::Free()
{
	__super::Free();
}
