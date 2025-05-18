#include "IceBeamWeapon.h"
#include "Export_Function.h"

#include "BulletMgr.h"
#include "IceBullet.h"
#include "..\Engine\SoundMgr.h"

CIceBeamWeapon::CIceBeamWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
	Set_ObjTag(L"IceBeamWeapon");

	m_fCycle = 1.0f;
	m_MaxBulletNum = 10;
	m_CurBulletNum = 10;
}

CIceBeamWeapon::~CIceBeamWeapon()
{
}

CBullet* CIceBeamWeapon::Shot_Setting()
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

	CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"IceBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, { 1.7f,1.7f,1.f }, false, 20.f);

	
	STOP_PLAY_SOUND(L"sfxLaser.wav", SOUND_EJECT, 1.f);
	return bullet;
}

_int CIceBeamWeapon::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CIceBeamWeapon::Add_Component()
{
	/*CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });*/
	return S_OK;
}

HRESULT CIceBeamWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CIceBeamWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CIceBeamWeapon::Render_GameObject(void)
{

	__super::Render_GameObject();
}

CIceBeamWeapon* CIceBeamWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CIceBeamWeapon*		pInstance = new CIceBeamWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CIceBeamWeapon::Free(void)
{
	__super::Free();
}


