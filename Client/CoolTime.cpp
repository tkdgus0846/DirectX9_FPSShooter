#include "CoolTime.h"

#include "Export_Function.h"

CCoolTime::CCoolTime(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_bIsCall(false)
{
}

CCoolTime::CCoolTime(const CCoolTime & rhs)
	: CBehavior(rhs), m_bIsCall(rhs.m_bIsCall)
{
}

CCoolTime::~CCoolTime()
{
}

HRESULT CCoolTime::Ready_Behavior()
{
	m_fCurTime = Get_WorldTime();
	m_fPreTime = Get_WorldTime();

	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CCoolTime::Update_Component(const _float & fTimeDelta)
{
	if(m_bIsCall)
		m_fCurTime = Get_WorldTime();
	else
	{
		m_bIsCall = true;
		m_fPreTime = Get_WorldTime();
		return BEHAVIOR_FAIL;
	}

	if (m_fCurTime - m_fPreTime > m_fTimer)
	{
		m_fPreTime = m_fCurTime;
		m_bIsCall = false;
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_FAIL;
}

CCoolTime * CCoolTime::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCoolTime* pInstance = new CCoolTime(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CCoolTime::Clone(void)
{
	return new CCoolTime(*this);
}

void CCoolTime::Free()
{
	__super::Free();
}
