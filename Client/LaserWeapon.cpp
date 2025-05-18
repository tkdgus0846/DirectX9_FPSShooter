#include "LaserWeapon.h"
#include "Export_Function.h"
#include "SoundMgr.h"
#include "BulletMgr.h"
#include "LaserBullet.h"

CLaserWeapon::CLaserWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
	Set_ObjTag(L"LaserWeapon");

	m_fCycle = 0.5f;
	m_MaxBulletNum = 30.f;
	m_CurBulletNum = 30.f;
}

CLaserWeapon::~CLaserWeapon()
{
}



CBullet* CLaserWeapon::Shot_Setting()
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

	CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"LaserBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, { 10.f,1.f,1.f }, false, 200.f);

	bullet->m_pTransform->Rot_Yaw(-90.f, 1.f);

	STOP_PLAY_SOUND(L"sfxLaser.wav", SOUND_ENVIRONMENT, 1.f);
	//m_CurBulletNum++;

	return bullet;
}

_int CLaserWeapon::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CLaserWeapon::Add_Component()
{

	/*CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });*/
	return S_OK;
}

HRESULT CLaserWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CLaserWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CLaserWeapon::Render_GameObject(void)
{

	__super::Render_GameObject();
}

CLaserWeapon* CLaserWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CLaserWeapon*		pInstance = new CLaserWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLaserWeapon::Free(void)
{
	__super::Free();
}