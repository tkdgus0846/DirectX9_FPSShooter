#include "SwordWeapon.h"
#include "Export_Function.h"

#include "BulletMgr.h"
#include "SwordBullet.h"
#include "..\Engine\SoundMgr.h"

CSwordWeapon::CSwordWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
	Set_ObjTag(L"SwordWeapon");

	m_fCycle = 0.3f;
	m_MaxBulletNum = 50;
	m_CurBulletNum = 50;

	m_OffsetArr[0] = { 1.8f, -0.5f, 4.7f };
	m_OffsetArr[1] = { 0.90f, -0.75f, 4.7f };
	m_OffsetArr[2] = { 0.00f, -1.0f,4.7f };
	m_OffsetArr[3] = { -0.90f,-0.75f, 4.7f };
	m_OffsetArr[4] = { -1.8f,-0.5f, 4.7f };

	for (int i = 0; i < 5; i++)
	{
		m_SwordPreparedArr[i] = false;
	}
		
	m_fGatherTime = 0.f;
	m_GatheredSword = 0;
}

CSwordWeapon::~CSwordWeapon()
{
}

void CSwordWeapon::Gather_Sword(const _float& fTimeDelta)
{
	if (m_GatheredSword >= 5) return;
	if (m_CurBulletNum <= 0) return;

	m_fGatherTime += fTimeDelta;

	
	if (m_fGatherTime > 0.4f)
	{
		m_fGatherTime = 0.f;

		if (m_SwordPreparedArr[2] == false)
			m_SwordPreparedArr[2] = true;
		else if (m_SwordPreparedArr[1] == false)
			m_SwordPreparedArr[1] = true;
		else if (m_SwordPreparedArr[3] == false)
			m_SwordPreparedArr[3] = true;
		else if (m_SwordPreparedArr[0] == false)
			m_SwordPreparedArr[0] = true;
		else if (m_SwordPreparedArr[4] == false)
			m_SwordPreparedArr[4] = true;

		STOP_PLAY_SOUND(L"sfxFrozen.wav", SOUND_EJECT, 1.f);

		SpendBullet();
		m_GatheredSword += 1.f;
	}
}

void CSwordWeapon::Shot()
{
	if (m_GatheredSword == 0)
	{
		m_fGatherTime = 0.f;
		return;
	}

	for (int i = 0; i < m_GatheredSword; i++)
	{
		CBullet* bullet = Sword_Shot_Setting(i);

		if (bullet)
		{
			//cout << m_CurBulletNum << endl;
		}
	}

	m_SwordBulletArr.clear();
	m_SwordBulletArr.resize(0);
	m_GatheredSword = 0;
	m_fGatherTime = 0.f;

	for (int i = 0; i < 5; i++)
	{
		m_SwordPreparedArr[i] = false;
	}
}

CBullet* CSwordWeapon::Sword_Shot_Setting(_int iIndex)
{
	CCamera* playerCamera = dynamic_cast<CCamera*>(Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE));

	if (playerCamera == nullptr) return nullptr;


	VIEWPARAMS* cameraViewparams = playerCamera->Get_Camera_ViewParams();
	_vec3 cameraAt = cameraViewparams->vAt;
	_vec3 cameraEye = cameraViewparams->vEye;

	_vec3 look = cameraAt - cameraEye;

	look = look*12.f;

	cameraAt = cameraEye + look;

	_vec3 bulletDir = cameraAt - m_SwordBulletArr[iIndex]->m_pTransform->m_vInfo[INFO_POS];
	bulletDir.Normalize();

	m_SwordBulletArr[iIndex]->SetSpeed(50.f);
	m_SwordBulletArr[iIndex]->Set_Dir(bulletDir);

	return m_SwordBulletArr[iIndex];
}

_int CSwordWeapon::Update_GameObject(const _float& fTimeDelta)
{
	_matrix cameraRotationMat, viewMat;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMat);
	viewMat.Inverse();

	for (int i = 0; i < 5; i++)
	{
		D3DXVec3TransformCoord(&m_PosArr[i], &m_OffsetArr[i], &viewMat);
	}

	if (m_SwordPreparedArr[2] == true && m_SwordBulletArr.size() < 1)
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"SwordBullet", m_pGraphicDev, m_PosArr[2], { viewMat._31,viewMat._32,viewMat._33 }, { 0.5f,0.5f,1.f }, false, 0.f);
		m_SwordBulletArr.push_back(bullet);
		Add_GameObject(bullet);
	}
	else if (m_SwordPreparedArr[1] == true && m_SwordBulletArr.size() < 2)
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"SwordBullet", m_pGraphicDev, m_PosArr[1], { viewMat._31,viewMat._32,viewMat._33 }, { 0.5f,0.5f,1.f }, false, 0.f);
		m_SwordBulletArr.push_back(bullet);
		Add_GameObject(bullet);
	}
	else if (m_SwordPreparedArr[3] == true && m_SwordBulletArr.size() < 3)
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"SwordBullet", m_pGraphicDev, m_PosArr[3], { viewMat._31,viewMat._32,viewMat._33 }, { 0.5f,0.5f,1.f }, false, 0.f);
		m_SwordBulletArr.push_back(bullet);
		Add_GameObject(bullet);
	}
	else if (m_SwordPreparedArr[0] == true && m_SwordBulletArr.size() < 4)
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"SwordBullet", m_pGraphicDev, m_PosArr[0], { viewMat._31,viewMat._32,viewMat._33 }, { 0.5f,0.5f,1.f }, false, 0.f);
		m_SwordBulletArr.push_back(bullet);
		Add_GameObject(bullet);
	}
	else if (m_SwordPreparedArr[4] == true && m_SwordBulletArr.size() < 5)
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"SwordBullet", m_pGraphicDev, m_PosArr[4], { viewMat._31,viewMat._32,viewMat._33 }, { 0.5f,0.5f,1.f }, false, 0.f);
		m_SwordBulletArr.push_back(bullet);
		Add_GameObject(bullet);
	}

	

	for (int i = 0; i < m_SwordBulletArr.size(); i++)
	{
		if (i == 0)
		{			
			m_SwordBulletArr[i]->Set_Pos(m_PosArr[2]);
		}			
		else if (i == 1)
		{
			m_SwordBulletArr[i]->Set_Pos(m_PosArr[1]);
		}		
		else if (i == 2)
		{
			m_SwordBulletArr[i]->Set_Pos(m_PosArr[3]);
		}		
		else if (i == 3)
		{
			m_SwordBulletArr[i]->Set_Pos(m_PosArr[0]);
		}		
		else if (i == 4)
		{
			m_SwordBulletArr[i]->Set_Pos(m_PosArr[4]);
		}

		m_SwordBulletArr[i]->Set_Dir({ viewMat._31, viewMat._32, viewMat._33 });	
	}
	
	return 0;
}

HRESULT CSwordWeapon::Add_Component()
{
	return S_OK;
}

HRESULT CSwordWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CSwordWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSwordWeapon::Render_GameObject(void)
{

	__super::Render_GameObject();
}

CSwordWeapon* CSwordWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CSwordWeapon*		pInstance = new CSwordWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSwordWeapon::Free(void)
{
	__super::Free();
}
