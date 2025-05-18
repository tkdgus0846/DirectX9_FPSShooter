#include "Parabola.h"

#include "Export_Function.h"

CParabola::CParabola(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_fTime(0.f)
	, m_fForce(0.f), m_bStart(false), m_FstSpeed(0.f)
{
}

CParabola::CParabola(const CParabola & rhs)
	: CBehavior(rhs), m_fTime(rhs.m_fTime)
	, m_fForce(rhs.m_fForce), m_bStart(rhs.m_bStart)
	, m_FstSpeed(rhs.m_FstSpeed)
{
}

CParabola::~CParabola()
{
}

HRESULT CParabola::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();
	m_fForce = 5.f;
	return result;
}

_int CParabola::Update_Component(const _float & fTimeDelta)
{
	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);
	
	if (!m_bStart)
	{
		m_FstSpeed = fSpeed;
		fSpeed *= 2.f;
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);
		_vec3 vLook = Get_Player()->m_pTransform->m_vInfo[INFO_POS] - m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
		m_vDir = _vec3(vLook.x, 0.f, vLook.z).Normalize();
		m_bStart = true;
	}

	m_fTime += fTimeDelta;
	_float fY = m_fForce * m_fTime - 4.9f * m_fTime * m_fTime;
	_vec3 vDir = _vec3(m_vDir.x * m_fForce * m_fTime, fY, m_vDir.z * m_fForce * m_fTime).Normalize();

	m_pGameObject->m_pTransform->Set_Dir(vDir);

	if (m_fTime > 4.f)
	{
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", m_FstSpeed), BEHAVIOR_ERROR);
		m_fPreTime = m_fCurTime;
		m_fTime = 0.f;
		m_bStart = false;

		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

void CParabola::Render_Component(void)
{
	__super::Render_Component();
}

CParabola * CParabola::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CParabola* pInstance = new CParabola(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CParabola::Clone(void)
{
	return new CParabola(*this);
}

void CParabola::Free()
{
	__super::Free();
}