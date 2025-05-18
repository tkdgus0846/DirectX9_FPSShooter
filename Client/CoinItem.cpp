#include "CoinItem.h"
#include "Export_Function.h"
#include "Player.h"
#include "ItemManager.h"
#include "..\Engine\SoundMgr.h"

CCoinItem::CCoinItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
	Set_ObjTag(L"CoinItem");

	m_fY = 1.f;
	m_fMaxY = m_fY + 0.5f;
	m_fMinY = m_fY - 0.5f;
}

CCoinItem::~CCoinItem()
{
}

HRESULT CCoinItem::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	m_pAniCom = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAniCom, E_FAIL);

	RandCoin();

	m_pAniCom->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAniCom });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 1.0f, 1.0f, 1.0f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 10.f, 3.0f, 10.f });

	return S_OK;
}

HRESULT CCoinItem::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);

	return S_OK;
}

_int CCoinItem::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead()) return OBJ_RETPOOL;

	if (m_bDrop == true) ItemPatrol(fTimeDelta);
	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CCoinItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCoinItem::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

void CCoinItem::SetDead(_bool bDead /*= true*/)
{
	__super::SetDead(bDead);
	if (bDead == true)
		CItemManager::GetInstance()->Push(L"CoinItem", this);
}

CCoinItem * CCoinItem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCoinItem* pInstance = new CCoinItem(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void CCoinItem::RandCoin()
{
	int randNum = rand() % 2;

	if (randNum == 0)
	{
		// 큰코인은 UI 이미지랑 같이 사용중.
		CTexture* BigCoin = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Coin_Texture", this));
		m_pTransform->m_vScale = { 0.5f, 0.5f, 0.f };
		m_pTransform->Set_Pos(2.f, 0.5f, 10.f);
		m_uMapComponent[ID_RENDER].insert({ L"Coin_Texture", BigCoin });
		m_pAniCom->BindAnimation(ANIM_IDLE, BigCoin, 0.15f);
		m_eID = BIG;
	}
	else
	{
		CTexture* SmallCoin = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SmallCoin_Texture", this));
		m_pTransform->m_vScale = { 0.25f, 0.25f, 0.f };
		m_pTransform->Set_Pos(2.f, 0.25f, 10.f);
		m_uMapComponent[ID_RENDER].insert({ L"SmallCoin_Texture", SmallCoin });
		m_pAniCom->BindAnimation(ANIM_IDLE, SmallCoin, 0.15f);
		m_eID = SMALL;
	}
}

void CCoinItem::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);
	
	if (pPlayer && collsion->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		if (m_eID == BIG)
		{
			pPlayer->Gain_Coin(2);
		}
		else
		{
			pPlayer->Gain_Coin(1);
		}
	}

}

void CCoinItem::OnCollisionStay(const Collision * collision)
{
	if (dynamic_cast<CPlayer*>(collision->OtherGameObject) == nullptr)
	{
		return;
	}

	__super::OnCollisionStay(collision);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);
	if (pPlayer == nullptr) return;

	if (pPlayer && collision->MyCollider == Get_Component(L"Range", ID_ALL))
	{
		PLAY_SOUND(L"sfxCoin.wav", SOUND_LOOT, 1.f);
	}

	ItemMagnetic(pPlayer);
}

void CCoinItem::Free()
{
	__super::Free();
}