#include "stdafx.h"
#include "Wait.h"

#include "Export_Utility.h"

CWait::CWait(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_bRetVal(false)
{
}

CWait::CWait(const CWait & rhs)
	: CBehavior(rhs), m_bRetVal(rhs.m_bRetVal)
{
}

CWait::~CWait()
{
}


HRESULT CWait::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CWait::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;
	
	CAnimation* pAnimation = dynamic_cast<CAnimation*>(m_pGameObject->Get_Component(L"Animation", ID_ALL));
	if (pAnimation)
		pAnimation->SelectState(ANIM_IDLE);

	if (m_fCurTime - m_fPreTime >= m_fTimer)
	{
		m_fPreTime = m_fCurTime;

		if (m_bRetVal == true)
			return BEHAVIOR_SUCCES;
		else
			return BEHAVIOR_FAIL;
	}

	return BEHAVIOR_RUNNING;
}

CWait * CWait::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWait* pInstance = new CWait(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CWait::Clone(void)
{
	return new CWait(*this);
}

void CWait::Free()
{
	__super::Free();
}
