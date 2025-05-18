#include "LookAtPlayer.h"

#include "Player.h"
#include "Export_Function.h"

CLookAtPlayer::CLookAtPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_fFstSpeed(0.f)
	, m_bStart(false), m_fTime(0.f)
{
}

CLookAtPlayer::CLookAtPlayer(const CLookAtPlayer & rhs)
	: CBehavior(rhs), m_fFstSpeed(rhs.m_fFstSpeed)
	, m_bStart(rhs.m_bStart), m_fTime(rhs.m_fTime)
{
}

CLookAtPlayer::~CLookAtPlayer()
{
}

HRESULT CLookAtPlayer::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CLookAtPlayer::Update_Component(const _float & fTimeDelta)
{
	m_fTime += fTimeDelta;

	if (Get_Player())
		return BEHAVIOR_FAIL;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);

	if (!m_bStart)
	{
		m_fFstSpeed = fSpeed;
		fSpeed = dynamic_cast<CPlayer*>(Get_Player())->Get_Speed() * 1.2f;
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);
		m_bStart = true;
	}

	_vec3 vDir = Get_Player()->m_pTransform->m_vInfo[INFO_POS] - m_pGameObject->m_pTransform->m_vInfo[INFO_POS];
	vDir.Normalize();
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

CLookAtPlayer * CLookAtPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLookAtPlayer* pInstance = new CLookAtPlayer(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CLookAtPlayer::Clone(void)
{
	return new CLookAtPlayer(*this);
}

void CLookAtPlayer::Free()
{
	__super::Free();
}
