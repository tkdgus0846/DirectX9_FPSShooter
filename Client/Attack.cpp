#include "stdafx.h"
#include "Attack.h"

#include "Export_Function.h"
#include "BulletMgr.h"
#include "NormalBullet.h"
#include "RedLaserBullet.h"
#include "..\Engine\SoundMgr.h"

CAttack::CAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_pKey(nullptr)
	, m_fSpeed(0.f), m_bAtkPoint(false)
{
	ZeroMemory(m_vScale, sizeof(_vec3));
}

CAttack::CAttack(const CAttack & rhs)
	: CBehavior(rhs), m_pKey(rhs.m_pKey)
	, m_fSpeed(rhs.m_fSpeed), m_bAtkPoint(rhs.m_bAtkPoint)
{
}

CAttack::~CAttack()
{
}

HRESULT CAttack::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CAttack::Update_Component(const _float & fTimeDelta)
{
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
			m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK], vScale, true, m_fSpeed);

		if (m_pKey == L"EnemyBullet")
		{
			STOP_PLAY_SOUND(L"sfxBigBullet.wav", SOUND_ENEMY, 1.f);
		}
		else if (m_pKey == L"RedLaserBullet")
		{	
			if (m_pGameObject->m_pTransform->Get_MoveType() == CTransform::LANDOBJECT)
				STOP_PLAY_SOUND(L"EnemyLaser.wav", SOUND_ENEMY, 1.f);
		}


		if (m_bAtkPoint)
			dynamic_cast<CRedLaserBullet*>(bullet)->AttackPoint_On();

		m_fPreTime = m_fCurTime;
		Add_GameObject(bullet);
	}
	return BEHAVIOR_SUCCES;
}

void CAttack::Render_Component(void)
{
	__super::Render_Component();
}

CAttack * CAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAttack* pInstance = new CAttack(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CAttack::Clone(void)
{
	return new CAttack(*this);
}

void CAttack::Free()
{
	__super::Free();
}
