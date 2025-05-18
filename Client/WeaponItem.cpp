#include "WeaponItem.h"
#include "Export_Function.h"
#include "Player.h"
#include "SoundMgr.h"

CWeaponItem::CWeaponItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
	Set_LayerID(LAYER_ROOM_ITEM);
	Set_ObjTag(L"WeaponItem");
	m_bDrop = true;
	m_bBill = false;
	m_bCanLoot = false;
}

CWeaponItem::~CWeaponItem()
{
}

HRESULT CWeaponItem::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	Select_Type();

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ROOMITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 1.5f, 3.0f, 1.5f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_ROOMITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 10.f, 3.0f, 10.f });

	return S_OK;
}

HRESULT CWeaponItem::Ready_GameObject(_vec3 vPos)
{
	_vec3 vScale = { 1.0f, 1.0f, 0.f };
	m_pTransform->Set_Pos(vPos);
	m_pTransform->Set_Scale(vScale);
	__super::Ready_GameObject();
	return S_OK;
}

_int CWeaponItem::Update_GameObject(const _float & fTimeDelta)
{
	WeaponRotationZ(fTimeDelta);
	m_fAngle += 180.f * fTimeDelta;

	__super::Update_GameObject(fTimeDelta);

	if (GetDead()) return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CWeaponItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CWeaponItem::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CWeaponItem::OnCollisionEnter(const Collision * collsion)
{
	if (m_bCanLoot == false) return;

	__super::OnCollisionEnter(collsion);

}

void CWeaponItem::OnCollisionStay(const Collision * collision)
{
	if (m_bCanLoot == false) return;
	__super::OnCollisionStay(collision);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);

	if (pPlayer == nullptr) return;

	if (pPlayer && collision->MyCollider == Get_Component(L"Range", ID_ALL))
	{	
		
		CSoundMgr::GetInstance()->SetVolumeCurBGM(0.1f);
		STOP_PLAY_SOUND(L"Secret.wav", SOUND_LOOT, 1.f);
		pPlayer->Gain_Weapon(m_eID);
	}

	ItemMagnetic(pPlayer);
}

CWeaponItem * CWeaponItem::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, WEAPONTYPE eID)
{
	CWeaponItem* pInstance = new CWeaponItem(pGraphicDev);

	pInstance->Set_ID(eID);
	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CWeaponItem::Free(void)
{
	__super::Free();
}

void CWeaponItem::Select_Type()
{
	// UI랑 동일한이미지 사용
	switch (m_eID)
	{
		case BIGSHOT:
		{
			CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_bigshot_Texture", this));
			m_uMapComponent[ID_RENDER].insert({ L"Weapon_bigshot_Item_Texture", Texture });
			
		}
		break;
		case EXPLOSIVESHOT:
		{
			CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_explosiveshot_Texture", this));
			m_uMapComponent[ID_RENDER].insert({ L"Weapon_explosiveshot_Item_Texture", Texture });
		}
		break;
		case FLAMESHOT:
		{
			CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_flameshot_Texture", this));
			m_uMapComponent[ID_RENDER].insert({ L"Weapon_flameshot_Item_Texture", Texture });
		}
		break;
		case RAPIDSHOT:
		{
			CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_rapidshot_Texture", this));
			m_uMapComponent[ID_RENDER].insert({ L"Weapon_rapidshot_Item_Texture", Texture });
		}
		break;
		case SPREADSHOT:
		{
			CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_spreadshot_Texture", this));
			m_uMapComponent[ID_RENDER].insert({ L"Weapon_spreadshot_Item_Texture", Texture });
		}
		break;
		case FREEZESHOT:
		{
			CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_freezeshot_Texture", this));
			m_uMapComponent[ID_RENDER].insert({ L"Weapon_freezeshot_Item_Texture", Texture });
		}
		break;
		case LASERSHOT:
		{
			CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_lasershot_Texture", this));
			m_uMapComponent[ID_RENDER].insert({ L"Weapon_lasershot_Item_Texture", Texture });
	
		}
		break;
	}
}

void CWeaponItem::WeaponRotationZ(const _float & fTimeDelta) // 이게 Y네 Z가아니고 m_fAngle은 어디서 더해줌?
{
	_matrix matRot;
	_vec3	vecRot{ 1.f, 0.f, 1.f };
	D3DXMatrixRotationY(&matRot, D3DXToRadian(m_fAngle));
	D3DXVec3TransformCoord(&vecRot, &vecRot, &matRot);
	m_pTransform->m_vInfo[INFO_LOOK] = vecRot;
	m_pTransform->m_vInfo[INFO_RIGHT] = vecRot;
}
