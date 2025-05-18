#include "HeartItem.h"
#include "Export_Function.h"
#include "Player.h"
#include "ItemManager.h"
#include "..\Engine\SoundMgr.h"

CHeartItem::CHeartItem(LPDIRECT3DDEVICE9 pGraphicDev)
	:CItem(pGraphicDev)
{
	Set_ObjTag(L"HeartItem");

	m_fY = 1.f;
	m_fMaxY = m_fY + 0.5f;
	m_fMinY = m_fY - 0.5f;
}

CHeartItem::~CHeartItem()
{
}

HRESULT CHeartItem::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"HeartItem_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"HeartItem_Texture", Texture });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 1.0f, 1.0f, 1.0f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 10.f, 3.0f, 10.f });

	m_pTransform->Set_BillMode(true);

	return S_OK;
}

HRESULT CHeartItem::Ready_GameObject(void)
{
	_vec3 vScale = { 0.5f, 0.5f, 1.f };
	m_pTransform->Set_Pos(20.f, 1.f, 20.f);
	m_pTransform->Set_Scale(vScale);
	__super::Ready_GameObject();

	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);
	return S_OK;
}

_int CHeartItem::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead()) return OBJ_RETPOOL;

	if (m_bDrop == true) ItemPatrol(fTimeDelta);
	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CHeartItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CHeartItem::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CHeartItem::SetDead(_bool bDead /*= true*/)
{
	__super::SetDead(bDead);
	if (bDead == true)
		CItemManager::GetInstance()->Push(L"HeartItem", this);
}

CHeartItem * CHeartItem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHeartItem* pInstance = new CHeartItem(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CHeartItem::OnCollisionEnter(const Collision * collsion)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (pPlayer == nullptr) { return; }
	_int curHp = pPlayer->Get_HP();
	if (curHp == 20) { return; }

	__super::OnCollisionEnter(collsion);

	if (pPlayer && collsion->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		if (curHp < 20)
		{
			pPlayer->Gain_Hp();
		}
	}
}

void CHeartItem::OnCollisionStay(const Collision * collision)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);

	if (pPlayer == nullptr) { return; }
	_int curHp = pPlayer->Get_HP();
	if (curHp == 20) { return; }

	if (pPlayer == nullptr) return;

	if (pPlayer && collision->MyCollider == Get_Component(L"Range", ID_ALL))
	{
		PLAY_SOUND(L"sfxpickup.wav", SOUND_LOOT, 1.f);
	}

	__super::OnCollisionEnter(collision);

	ItemMagnetic(pPlayer);
}

void CHeartItem::Free(void)
{
	__super::Free();
}
