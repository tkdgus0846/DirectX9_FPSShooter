#include "MoveCos.h"

#include "Export_Function.h"

CMoveCos::CMoveCos(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_fTime(0.f)
	, m_bStart(false), m_fFstSpeed(0.f)
	, m_bIsFollow(false)
{
	ZeroMemory(&m_vDir, sizeof(_vec3));
}

CMoveCos::CMoveCos(const CMoveCos & rhs)
	: CBehavior(rhs), m_fTime(rhs.m_fTime)
	, m_bStart(rhs.m_bStart), m_fFstSpeed(rhs.m_fFstSpeed)
	, m_vDir(rhs.m_vDir), m_bIsFollow(rhs.m_bIsFollow)
{
}

CMoveCos::~CMoveCos()
{
}

HRESULT CMoveCos::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CMoveCos::Update_Component(const _float & fTimeDelta)
{
	m_fTime += fTimeDelta;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);

	if (!m_bStart)
	{
		m_fFstSpeed = fSpeed;
		fSpeed *= 2.f;
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);
		m_bStart = true;
		_vec3 vLook = Get_Player()->m_pTransform->m_vInfo[INFO_POS] - m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
		m_vDir = _vec3(vLook.x, 0.f, vLook.z).Normalize();
	}

	if (m_bIsFollow)
	{
		_vec3 vLook = Get_Player()->m_pTransform->m_vInfo[INFO_POS] - m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
		m_vDir = _vec3(vLook.x, 0.f, vLook.z).Normalize();
	}

	_float fVal = cosf(m_fTime * 4.f) * fSpeed - 2.f;

	_vec3 vDir = _vec3(m_vDir.x * fSpeed * m_fTime, fVal, m_vDir.z * fSpeed * m_fTime).Normalize();

	m_pGameObject->m_pTransform->Set_Dir(vDir);

	if (m_fTime > m_fTimer)
	{
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", m_fFstSpeed), BEHAVIOR_ERROR);
		m_fTime = 0.f;
		m_bStart = false;

		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

CMoveCos * CMoveCos::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMoveCos* pInstance = new CMoveCos(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CMoveCos::Clone(void)
{
	return new CMoveCos(*this);
}

void CMoveCos::Free()
{
	__super::Free();
}
