#include "NormalWeapon.h"
#include "Export_Function.h"

#include "BulletMgr.h"
#include "NormalBullet.h"
#include "IceBullet.h"
#include "SoundMgr.h"

CNormalWeapon::CNormalWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
	Set_ObjTag(L"NormalWeapon");

	m_fCycle = 0.5f;
	m_MaxBulletNum = 2;
	m_CurBulletNum = 2;
}

CNormalWeapon::~CNormalWeapon()
{
}

CBullet* CNormalWeapon::Shot_Setting()
{
	CCamera* playerCamera = dynamic_cast<CCamera*>(Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE));

	if (playerCamera == nullptr) return nullptr;


	VIEWPARAMS* cameraViewparams = playerCamera->Get_Camera_ViewParams();
	_vec3 cameraAt = cameraViewparams->vAt;
	_vec3 cameraEye = cameraViewparams->vEye;

	_vec3 look = cameraAt - cameraEye;

	look = look*30.f;

	cameraAt = cameraEye + look;


	_vec3 bulletDir = cameraAt - m_pTransform->m_vInfo[INFO_POS];
	bulletDir.Normalize();

	if (m_bTacticalScope && m_TacticalDir != _vec3{ 0,0,0 })
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"NormalBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], m_TacticalDir, { 0.5f,0.5f,1.f }, false, 40.f);
		STOP_PLAY_SOUND(L"sfxBigBullet.wav", SOUND_EJECT, 1.f);
		m_CurBulletNum++;

		return bullet;
	}
	else
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"NormalBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, { 0.5f,0.5f,1.f }, false, 40.f);
		STOP_PLAY_SOUND(L"sfxBigBullet.wav", SOUND_EJECT, 1.f);
		m_CurBulletNum++;

		return bullet;
	}

}


_int CNormalWeapon::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CNormalWeapon::Add_Component()
{

	/*CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });*/
	return S_OK;
}

HRESULT CNormalWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CNormalWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CNormalWeapon::Render_GameObject(void)
{
	
	__super::Render_GameObject();
}

CNormalWeapon* CNormalWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CNormalWeapon*		pInstance = new CNormalWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CNormalWeapon::Free(void)
{
	__super::Free();
}
