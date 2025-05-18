#include "stdafx.h"
#include "MoveLook.h"

#include "Export_Utility.h"

CMoveLook::CMoveLook(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_fMagnification(0.f)
{
}

CMoveLook::CMoveLook(const CMoveLook & rhs)
	: CBehavior(rhs), m_fMagnification(rhs.m_fMagnification)
{
}

CMoveLook::~CMoveLook()
{
}

HRESULT CMoveLook::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CMoveLook::Update_Component(const _float & fTimeDelta)
{
	CAnimation* pAnimation = dynamic_cast<CAnimation*>(m_pGameObject->Get_Component(L"Animation", ID_ALL));
	if (pAnimation)
		pAnimation->SelectState(ANIM_WALK);

	m_fCurTime += fTimeDelta;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);

	m_pGameObject->m_pTransform->Move_Walk(fSpeed * m_fMagnification, fTimeDelta);

	if (m_fCurTime - m_fPreTime >= m_fTimer)
	{
		m_fPreTime = m_fCurTime;
		return BEHAVIOR_SUCCES;
	}
	else
		return BEHAVIOR_RUNNING;
}

void CMoveLook::Render_Component(void)
{
	__super::Render_Component();
}

CComponent * CMoveLook::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMoveLook* pInstance = new CMoveLook(pGraphicDev);
	
	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CMoveLook::Clone(void)
{
	return new CMoveLook(*this);
}

void CMoveLook::Free()
{
	__super::Free();
}
