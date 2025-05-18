#include "SpreadWeapon.h"
#include "Export_Function.h"
#include "BulletMgr.h"
#include "NormalBullet.h"
#include "..\Engine\SoundMgr.h"


CSpreadWeapon::CSpreadWeapon(LPDIRECT3DDEVICE9 pGraphicDev)
	:CWeapon(pGraphicDev)
{
	Set_ObjTag(L"SpreadWeapon");

	this->m_fCycle = 1.f;
	this->m_MaxBulletNum = 1000.f;
	this->m_CurBulletNum = 1000.f;
}

CSpreadWeapon::~CSpreadWeapon()
{
}


void CSpreadWeapon::Shot()
{
	if (CanShot())
	{
		STOP_PLAY_SOUND(L"sfxBullet.wav", SOUND_EJECT, 1.f);
		for (size_t j = 0; j < 5; j++)
		{
			CBullet* bullet = Shot_Setting(j * 10.f - 20.f);

			if (bullet)
			{
				Add_GameObject(bullet);
				SpendBullet();
			}
		}
		m_bMaintain = true;
		m_bShooted = true;
		m_bEnableShot = false;
	}
}


CBullet * CSpreadWeapon::Shot_Setting(_float fAngle)
{
	CCamera* pCamera = dynamic_cast<CCamera*>(Engine::Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE));
	if (pCamera == nullptr)	{return nullptr;}

	VIEWPARAMS* pCameraviewparams = pCamera->Get_Camera_ViewParams();

	_vec3 vAt = pCameraviewparams->vAt;
	_vec3 vEye = pCameraviewparams->vEye;

	_vec3 Look = vAt - vEye;

	D3DXVECTOR3 bulletDir;
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(fAngle));
	D3DXVec3TransformNormal(&bulletDir, &Look, &rotationMatrix);

	D3DXVec3Normalize(&bulletDir, &bulletDir);
	

	CBullet* Bullet = CBulletMgr::GetInstance()->Pop(L"NormalBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, { 0.5f,0.5f,1.f }, false, 80.f);

	return Bullet;
}

_int CSpreadWeapon::Update_GameObject(const _float & fTimeDelta)
{
	m_fTime += fTimeDelta;
	if (m_bMaintain == true)
	{
		if (m_fCycle > 0.1f && m_fTime > 0.1f)
		{
			m_fCycle -= 0.01f;
			m_fTime = 0.f;
		}
	}
	else
	{
		m_fCycle = 1.f;
	}

	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CSpreadWeapon::Add_Component()
{
	return S_OK;
}

HRESULT CSpreadWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CSpreadWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSpreadWeapon::Render_GameObject(void)
{
	__super::Render_GameObject();
}

CSpreadWeapon * CSpreadWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform * pOnwerTransform)
{
	CSpreadWeapon* pInstance = new CSpreadWeapon(pGraphicDev);

	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		pInstance = nullptr;
	}

	return pInstance;
}

void CSpreadWeapon::Free(void)
{
	__super::Free();
}
