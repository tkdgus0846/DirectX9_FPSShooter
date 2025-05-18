#include "AttackToPlayer.h"

#include "Export_Function.h"
#include "BulletMgr.h"
#include "NormalBullet.h"
#include "RedLaserBullet.h"

CAttackToPlayer::CAttackToPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CAttackToPlayer::CAttackToPlayer(const CAttackToPlayer & rhs)
	: CBehavior(rhs)
{
}

CAttackToPlayer::~CAttackToPlayer()
{
}

HRESULT CAttackToPlayer::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CAttackToPlayer::Update_Component(const _float & fTimeDelta)
{
	if (!Get_Player())
		return BEHAVIOR_FAIL;

	m_fCurTime = Get_WorldTime();

	if (m_fCurTime - m_fPreTime > m_fTimer)
	{
		_vec3 vScale{ 1.f, 1.f, 1.f };
		_vec3 vLook = m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK];
		if (0 == lstrcmp(L"LaserBullet", m_pKey))
			vScale = m_vScale;

		CBullet* bullet = CBulletMgr::GetInstance()->Pop(
			m_pKey, m_pGraphicDev,
			m_pGameObject->m_pTransform->m_vInfo[INFO_POS],
			Get_Player()->m_pTransform->m_vInfo[INFO_POS] - m_pGameObject->m_pTransform->m_vInfo[INFO_POS], 
			vScale, true, m_fSpeed);

		if (m_bAtkPoint)
			dynamic_cast<CRedLaserBullet*>(bullet)->AttackPoint_On();

		m_fPreTime = m_fCurTime;
		Add_GameObject(bullet);
	}
	return BEHAVIOR_SUCCES;
}

void CAttackToPlayer::Render_Component(void)
{
}

CAttackToPlayer * CAttackToPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAttackToPlayer* pInstance = new CAttackToPlayer(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CAttackToPlayer::Clone(void)
{
	return new CAttackToPlayer(*this);
}

void CAttackToPlayer::Free()
{
	__super::Free();
}
