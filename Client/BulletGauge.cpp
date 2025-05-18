#include "BulletGauge.h"
#include "Export_Function.h"
#include "Player.h"
#include "Weapon.h"

CBulletGauge::CBulletGauge(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
	Set_ObjTag(L"BulletGauge");
}

CBulletGauge::~CBulletGauge()
{
}

HRESULT CBulletGauge::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CBulletGauge::Update_GameObject(const _float & fTimeDelta)
{
	CPlayer* player = dynamic_cast<CPlayer*>(Engine::Get_Player());
	if (player == nullptr) return 0;

	CWeapon* pWeapon = player->Get_CurWeapon();
	if (pWeapon == nullptr) return 0;

	switch (player->Get_CurWeaponType())
	{
	case BIGSHOT: 
	{
		m_pBufferCom->Edit_VB(m_NormalGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_NormalGuage = Cur / Max;
	}
		break;
	case EXPLOSIVESHOT:
	{
		m_pBufferCom->Edit_VB(m_ExplosiveGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_ExplosiveGuage = Cur / Max;
	}
		break;
	case FLAMESHOT: 
	{
		m_pBufferCom->Edit_VB(m_FlameGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_FlameGuage = Cur / Max;
	}
		break;
	case RAPIDSHOT:
	{
		m_pBufferCom->Edit_VB(m_RapidGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_RapidGuage = Cur / Max;
	}
		break;
	case SPREADSHOT:
	{
		m_pBufferCom->Edit_VB(m_SpreadGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_SpreadGuage = Cur / Max;
	}
		break;
	case FREEZESHOT: 
	{
		m_pBufferCom->Edit_VB(m_IceGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_IceGuage = Cur / Max; 
	}
		break;
	case LASERSHOT:
	{
		m_pBufferCom->Edit_VB(m_LaserGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_LaserGuage = Cur / Max;
	}
		break;
	}


	Engine::Add_RenderGroup(RENDER_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}


void CBulletGauge::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBulletGauge::Render_GameObject(void)
{
	if (Engine::Get_Player() == nullptr) { return; }
	if (dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_bAimHack() == true) { return; }

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	Set_ViewMatrix_UI();

	__super::Render_GameObject();
}

HRESULT CBulletGauge::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex_Dynamic", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex_Dynamic", pComponent });

	//cout << pComponent << endl;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BulletGauge_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"BulletGauge_Texture", pComponent });

	return S_OK;
}

void CBulletGauge::Set_ViewMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	D3DXMatrixScaling(&matView, 106.f, 12.f, 0.f);

	D3DXMATRIX translationMat;
	D3DXMatrixTranslation(&translationMat, -203.f, -230.f, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &translationMat);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

CBulletGauge * CBulletGauge::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBulletGauge* pInstance = new CBulletGauge(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBulletGauge::Free(void)
{
	__super::Free();
}






