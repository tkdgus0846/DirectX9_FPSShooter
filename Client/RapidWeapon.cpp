#include "RapidWeapon.h"
#include "Export_Function.h"

#include "BulletMgr.h"
#include "NormalBullet.h"
#include "IceBullet.h"
#include "..\Engine\SoundMgr.h"

CRapidWeapon::CRapidWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
	Set_ObjTag(L"RapidWeapon");

	m_fCycle = 0.15f;
	m_MaxBulletNum = 100;
	m_CurBulletNum = 100;
}

CRapidWeapon::~CRapidWeapon()
{
}

CBullet* CRapidWeapon::Shot_Setting()
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

	CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"NormalBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, { 0.5f,0.5f,1.f }, false, 80.f);

	STOP_PLAY_SOUND(L"sfxBigBullet.wav", SOUND_EJECT, 1.f);

	//m_CurBulletNum++;

	return bullet;
}

_int CRapidWeapon::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CRapidWeapon::Add_Component()
{

	/*CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });*/
	return S_OK;
}

HRESULT CRapidWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CRapidWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CRapidWeapon::Render_GameObject(void)
{

	__super::Render_GameObject();
}

CRapidWeapon* CRapidWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CRapidWeapon*		pInstance = new CRapidWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CRapidWeapon::Free(void)
{
	__super::Free();
}
