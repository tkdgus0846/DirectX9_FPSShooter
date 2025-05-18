#include "Tennel.h"

#include "Export_Function.h"

#include "RoomMgr.h"
#include "Door.h"
#include "Tile.h"
#include "Player.h"
#include "Room.h"
#include "LavaTile.h"
#include "SoundMgr.h"

CTennel::CTennel(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_pDoor(nullptr),
	m_bInTennel(false)
{
	Set_LayerID(LAYER_TENNEL);
	Set_ObjTag(L"Tennel");

}

CTennel::~CTennel()
{
}

HRESULT CTennel::Ready_GameObject(void)
{
	HRESULT Result = __super::Ready_GameObject();

	m_pTransform->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.f };
	m_pTransform->m_vScale = { 5.f, 5.f, 5.f };

	return Result;
}

_int CTennel::Update_GameObject(const _float & fTimeDelta)
{
	
	__super::Update_GameObject(fTimeDelta);

	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CTennel::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTennel::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();

}

void CTennel::OnCollisionEnter(const Collision * collsion)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (nullptr != pPlayer)
	{
		_int iRoomIdx = m_pDoor->Get_Room()->Get_Room_Index();
		CRoomMgr::GetInstance()->Set_CurRoom(iRoomIdx);
		CCollider* playerCol = dynamic_cast<CCollider*>(pPlayer->Get_Component(L"BodyCollider", ID_ALL));
		if (playerCol != nullptr)
			playerCol->Get_CollisionList().clear();

		// 임의로 추가함
		ROOM_MGR->Set_In_Tennel(false);

		if ((*ROOM_MGR->Get_CurRoom()->GetLayerVec())[LAYER_NPC]->Get_ObjectSize() != 0)
		{
			STOP_ALL_BGM;
			PLAY_BGM(L"Shop.wav", SOUND_BGM_SHOP, BGM_SOUND_VOLUME);
		}
		else
		{
			if (!IS_PLAYING(SOUND_BGM_FIELD))
			{
				STOP_ALL_BGM;

				switch (m_eStageInfo)
				{
				case STAGE1:
					PLAY_BGM(L"Sector1.wav", SOUND_BGM_FIELD, BGM_SOUND_VOLUME);
					break;
				case STAGE2:
					PLAY_BGM(L"Sector2.wav", SOUND_BGM_FIELD, BGM_SOUND_VOLUME);
					break;
				case STAGE3:
					PLAY_BGM(L"Sector3.wav", SOUND_BGM_FIELD, BGM_SOUND_VOLUME);
					break;
				case STAGE4:
					PLAY_BGM(L"Sector4.wav", SOUND_BGM_FIELD, BGM_SOUND_VOLUME);
					break;
				}
				
			}
		}

		_vec3 vLook = pPlayer->m_pTransform->m_vInfo[INFO_LOOK];
		_vec3 vDoorLook = m_pDoor->m_pTransform->m_vInfo[INFO_LOOK];
		vLook.Normalize();
		vDoorLook.Normalize();
		_float fAngle = vLook.Degree(vDoorLook);
		pPlayer->m_pTransform->Rot_Yaw(fAngle, 1.f);
		pPlayer->m_pTransform->m_vInfo[INFO_POS] = m_pDoor->m_pTransform->m_vInfo[INFO_POS] + m_pDoor->m_pTransform->m_vInfo[INFO_LOOK] * 3.f;
		

		if (m_pDoor->Get_Door_Dir() == DOOR_WEST)
			pPlayer->m_pTransform->Rot_Yaw(180.f, 1.f);
	}
}

HRESULT CTennel::Add_Component()
{
	CCubeTex* pBufferCom = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"CubeTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"CubeTex", pBufferCom });

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_TENNEL));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	return S_OK;
}

void CTennel::Set_Position(_int iFrontorBack)
{
	m_pTransform->m_vInfo[INFO_POS] = { -30.f, 0.f, -30.f };
	m_pTransform->m_vInfo[INFO_POS] += _vec3(0.f, 0.f, -10.f) * iFrontorBack;
	_vec3 vPos = m_pTransform->m_vInfo[INFO_POS];
	
	if (0 == iFrontorBack)	// front ÀÎ °æ¿ì
	{
		m_pCollider->Set_BoundingBox({ 10.f, 10.f, 1.f }, _vec3(0.f, 0.f, 5.f));

		//m_pTile = CTile::Create(m_pGraphicDev, vPos + _vec3(0.f, 0.f, 5.f), L"Open_Texture");
	}
	else
	{
		m_pCollider->Set_BoundingBox({ 10.f, 10.f, 1.f }, -_vec3(0.f, 0.f, 5.f));
	}

}

void CTennel::Set_Tennel_Texture(STAGEINFO stageInfo)
{
	m_eStageInfo = stageInfo;
	switch (stageInfo)
	{
	case STAGE1:
		Change_Texture(L"Tennel_Texture", L"Level1_Tennel_Texture");
		break;
	case STAGE2:
		Change_Texture(L"Tennel_Texture", L"Level2_Tennel_Texture");
		break;
	case STAGE3:
		Change_Texture(L"Tennel_Texture", L"Level3_Tennel_Texture");
		break;
	case STAGE4:
		Change_Texture(L"Tennel_Texture", L"Level4_Tennel_Texture");
		break;
	default:
		break;
	}
	
}

CTennel * CTennel::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTennel* pInstance = new CTennel(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTennel::Free(void)
{
	//Safe_Release(m_pTile);
	__super::Free();
}
