#include "Weapon.h"
#include "Export_Function.h"
#include "Bullet.h"

CWeapon::CWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev),
	m_fAccTime(0.f),
	m_bEnableShot(true),
	m_fCycle(1.0f),
	m_bShooted(false),
	m_TacticalDir({ 0.f, 0.f, 0.f })

{
	m_vOffsetTrans = { 0.65f,-1.0f,3.7f };
}

CWeapon::~CWeapon()
{
}

void CWeapon::Shot()
{
	if (CanShot())
	{
		CBullet* bullet = Shot_Setting();

		if (bullet)
		{
			Add_GameObject(bullet);
			SpendBullet();
		}

		m_bShooted = true;
		m_bEnableShot = false;
	}
}

_int CWeapon::Update_GameObject(const _float& fTimeDelta)
{
	m_fAccTime += fTimeDelta;

	if (m_fAccTime >= m_fCycle && m_bShooted == true)
	{
		m_bEnableShot = true;
		m_fAccTime = 0.f;
		m_bShooted = false;
	}
	else
	{
		//m_bEnableShot = false;
		if (m_bShooted == false) m_fAccTime = 0.f;
	}

	_matrix cameraRotationMat, viewMat;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMat);
	viewMat.Inverse();

	D3DXVec3TransformCoord(&m_pTransform->m_vInfo[INFO_POS], &m_vOffsetTrans, &viewMat);
	
	return __super::Update_GameObject(fTimeDelta);
}

