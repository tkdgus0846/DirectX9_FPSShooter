#include "DiscItem.h"
#include "Export_Function.h"
#include "Player.h"
#include "..\Engine\SoundMgr.h"
#include "Portal.h"
#include "RoomMgr.h"

CDiscItem::CDiscItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
	Set_ObjTag(L"DiscItem");

	m_fY = 1.f;
	m_fMaxY = m_fY + 0.5f;
	m_fMinY = m_fY - 0.5f;
}

CDiscItem::~CDiscItem()
{
}

HRESULT CDiscItem::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Disc_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"DiscItem_Texture", Texture });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.2f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 1.0f, 1.0f, 1.0f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"RangeCollider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"RangeCollider", pCollider });
	pCollider->Set_BoundingBox({ 10.f, 3.0f, 10.f });

	return S_OK;
}

HRESULT CDiscItem::Ready_GameObject(void)
{
	_vec3 vScale = { 1.f, 1.f, 1.f };
	Set_Pos({ 85.f, 10.f, 85.f });
	m_pTransform->Set_Scale(vScale);

	m_bDrop = true;
	__super::Ready_GameObject();
	return S_OK;
}

_int CDiscItem::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	m_pTransform->m_vInfo[INFO_POS].y -= 2.f * fTimeDelta;

	if (m_pTransform->m_vInfo[INFO_POS].y < 3.f)
		m_pTransform->m_vInfo[INFO_POS].y = 3.f;

	//if (m_bDrop == true) ItemPatrol(fTimeDelta);
	__super::Update_GameObject(fTimeDelta);	

	return OBJ_NOEVENT;
}

void CDiscItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CDiscItem::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

void CDiscItem::SetDead(_bool bDead /*= true*/)
{
	__super::SetDead(bDead);

	if (GetDead())
	{
		_vec3 discPos = m_pTransform->m_vInfo[INFO_POS];

		if (CRoomMgr::GetInstance()->Get_CurStageInfo() == STAGE4)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_Player());

			player->Set_FlyMode();

			CCamera* camera = CCameraMgr::GetInstance()->Get_CurCamera();
			camera->Set_ProjParams(
				PROJPARAMS(
				D3DXToRadian(60.f),
				(_float)WINCX / WINCY,
				1.0f, 1000.f));

			STOP_ALL_BGM;
			CRenderer::GetInstance()->ToggleRenderUI();
			CManagement::GetInstance()->Set_Ending();

			return;
		}
		
		CPortal* portal = CPortal::Create(m_pGraphicDev, {85.f, 4.f, 61.f});
		Add_GameObject(portal);
	}
}

CDiscItem * CDiscItem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDiscItem* pInstance = new CDiscItem(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CDiscItem::OnCollisionEnter(const Collision * collsion)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);


	if (pPlayer && collsion->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		pPlayer->Gain_Disc(1);
	}

	__super::OnCollisionEnter(collsion);
}

void CDiscItem::OnCollisionStay(const Collision * collision)
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

void CDiscItem::Free(void)
{
	__super::Free();
}
