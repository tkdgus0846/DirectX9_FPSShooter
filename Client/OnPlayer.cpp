#include "OnPlayer.h"

#include "Export_Function.h"

COnPlayer::COnPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

COnPlayer::COnPlayer(const COnPlayer & rhs)
	: CBehavior(rhs)
{
}

COnPlayer::~COnPlayer()
{
}

HRESULT COnPlayer::Ready_Behavior()
{
	m_fCurTime = 0.f;

	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int COnPlayer::Update_Component(const _float & fTimeDelta)
{
	if (!Get_Player())
		return BEHAVIOR_FAIL;

	m_fCurTime += fTimeDelta;

	_vec3 vPos = Get_Player()->m_pTransform->m_vInfo[INFO_POS];
	m_pGameObject->m_pTransform->m_vInfo[INFO_POS] = { vPos.x, m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y, vPos.z };
	
	if (m_fCurTime >= m_fTimer)
	{
		m_fCurTime = 0.f;
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

void COnPlayer::LateUpdate_Component(void)
{
}

void COnPlayer::Render_Component(void)
{
}

COnPlayer * COnPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	COnPlayer* pInstance = new COnPlayer(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * COnPlayer::Clone(void)
{
	return new COnPlayer(*this);
}

void COnPlayer::Free()
{
	__super::Free();
}
