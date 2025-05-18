#include "MovePoint.h"

#include "Export_Function.h"

CMovePoint::CMovePoint(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_bStart(false)
	, m_fFstSpeed(0.f)
{
	ZeroMemory(&m_vDest, sizeof(_vec3));
}

CMovePoint::CMovePoint(const CMovePoint & rhs)
	: CBehavior(rhs), m_bStart(rhs.m_bStart)
	, m_fFstSpeed(rhs.m_fFstSpeed)
{
}

CMovePoint::~CMovePoint()
{
}

HRESULT CMovePoint::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CMovePoint::Update_Component(const _float & fTimeDelta)
{
	if (m_bStart == false)
	{
		_int iX = 0, iZ = 0;
		_float fSpeed = 0.f;

		FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);
		FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"iIndexX", iX), BEHAVIOR_ERROR);
		FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"iIndexZ", iZ), BEHAVIOR_ERROR);

		m_fFstSpeed = fSpeed;
		fSpeed *= 2.f;
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);
		m_vDest = { _float(iX) * 60.f + GetRandomFloat(2.f, 48.f) , -4.f, _float(iZ) * 60.f + GetRandomFloat(2.f, 48.f) };
		m_bStart = true;
	}

	_vec3 vDir = m_vDest - m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
	_float fDistance = vDir.Length();
	vDir.Normalize();
	m_pGameObject->m_pTransform->Set_Dir(vDir);

	if (fDistance < 1.f)
	{
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", m_fFstSpeed), BEHAVIOR_ERROR);
		m_bStart = false;
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

CMovePoint * CMovePoint::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMovePoint* pInstance = new CMovePoint(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CMovePoint::Clone(void)
{
	return new CMovePoint(*this);
}

void CMovePoint::Free()
{
	__super::Free();
}
