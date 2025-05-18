#include "ExplosiveWeapon.h"
#include "Export_Function.h"

#include "BulletMgr.h"
#include "NormalBullet.h"
#include "IceBullet.h"

CExplosiveWeapon::CExplosiveWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
	Set_ObjTag(L"ExplosiveWeapon");

	m_fCycle = 0.5f;
	m_MaxBulletNum = 2;
	m_CurBulletNum = 2;
}

CExplosiveWeapon::~CExplosiveWeapon()
{
}

CBullet* CExplosiveWeapon::Shot_Setting()
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

	CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"NormalBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, {0.5f,0.5f,1.f}, false, 40.f);

	m_CurBulletNum++;

	return bullet;	
}

_int CExplosiveWeapon::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CExplosiveWeapon::Add_Component()
{

	/*CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });*/
	return S_OK;
}

HRESULT CExplosiveWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CExplosiveWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CExplosiveWeapon::Render_GameObject(void)
{
	
	__super::Render_GameObject();
}

CExplosiveWeapon* CExplosiveWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CExplosiveWeapon*		pInstance = new CExplosiveWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CExplosiveWeapon::Free(void)
{
	__super::Free();
}
