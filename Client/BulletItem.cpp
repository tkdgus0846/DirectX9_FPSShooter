#include "BulletItem.h"
#include "Export_Function.h"
#include "Player.h"
#include "Weapon.h"
#include "ItemManager.h"
#include "..\Engine\SoundMgr.h"
CBulletItem::CBulletItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
	Set_ObjTag(L"BulletItem");
	m_fY = 1.f;
	m_fMaxY = m_fY + 0.5f;
	m_fMinY = m_fY - 0.5f;
}

CBulletItem::~CBulletItem()
{
}

HRESULT CBulletItem::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BulletItem_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"BulletItem_Texture", Texture });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.3f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 1.5f, 1.5f, 1.5f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 10.f, 3.0f, 10.f });

	

	return S_OK;
}

HRESULT CBulletItem::Ready_GameObject(void)
{
	_vec3 vScale = { 0.5f, 0.5f, 1.f };
	m_pTransform->Set_Pos(20.f, 1.f, 20.f);
	m_pTransform->Set_Scale(vScale);
	__super::Ready_GameObject();

	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);

	return S_OK;
}

_int CBulletItem::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead())
		return OBJ_RETPOOL;

	if (m_bDrop == true) ItemPatrol(fTimeDelta);
	__super::Update_GameObject(fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA, this);
	
	return OBJ_NOEVENT;
}

void CBulletItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBulletItem::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CBulletItem::SetDead(_bool bDead /*= true*/)
{
	__super::SetDead(bDead);
	if (bDead == true)
		CItemManager::GetInstance()->Push(L"BulletItem", this);
}

CBulletItem * CBulletItem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBulletItem* pInstance = new CBulletItem(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CBulletItem::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (pPlayer && collsion->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		CWeapon* pWeapon = pPlayer->Get_CurWeapon();
		_int maxBullet = pWeapon->Get_MaxBulletNum();
		_int curBullet = pWeapon->Get_CurBulletNum();
		if (curBullet / maxBullet  <  1.f)
		{
			pWeapon->GainBullet(2);
		}
	}
}

void CBulletItem::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);
	if (pPlayer == nullptr) return;

	if (pPlayer && collision->MyCollider == Get_Component(L"Range", ID_ALL))
	{
		PLAY_SOUND(L"sfxpickup.wav", SOUND_LOOT, 1.f);
	}
	ItemMagnetic(pPlayer);
}

void CBulletItem::Free(void)
{
	__super::Free();
}
