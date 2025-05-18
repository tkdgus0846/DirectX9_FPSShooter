#include "Door.h"

#include "Export_Function.h"


#include "RoomMgr.h"
#include "Room.h"
#include "Player.h"
#include "Tennel.h"

#include "Animation.h"


CDoor::CDoor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_pRoom(nullptr)
	, m_pInTennel(nullptr), m_pOutTennel(nullptr)
	, m_bCurDoorState(false), m_bPreDoorState(true)
{
	Set_LayerID(LAYER_TRIGGER);
	Set_ObjTag(L"Door");

}

CDoor::~CDoor()
{
}

HRESULT CDoor::Ready_GameObject(DOOR_DIR eDir, CRoom* pRoom)
{
	HRESULT Result = __super::Ready_GameObject();

	m_eDir = eDir;
	m_pRoom = pRoom;

	Set_Door_State();

	return Result;
}

_int CDoor::Update_GameObject(const _float & fTimeDelta)
{
	if (m_pInTennel == nullptr)
	{
		m_pInTennel = CRoomMgr::GetInstance()->Get_Tennel(0);
		m_pOutTennel = CRoomMgr::GetInstance()->Get_Tennel(1);

		/*m_pInTennel = SECTION_MGR->Get_Tennel(0);
		m_pOutTennel = SECTION_MGR->Get_Tennel(1);*/
	}

	//if (m_bCurDoorState != m_bPreDoorState)
	//{
	//	if (m_bCurDoorState == true)
	//	{
	//		// Open
	//	}
	//	else
	//	{
	//		// Close
	//	}
	//	m_pAnimation->SetInverse(!m_bCurDoorState);
	//	m_pCollider->Set_Enable(m_bCurDoorState);
	//	m_bPreDoorState = m_bCurDoorState;
	//}

	if (m_bCurDoorState)
	{
		m_pAnimation->SetInverse(false);
		m_pCollider->Set_Enable(m_bCurDoorState);
	}
	else
	{
		m_pAnimation->SetInverse(true);
		m_pCollider->Set_Enable(m_bCurDoorState);
	}

	if (GetDead()) return OBJ_DEAD;

	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Add_RenderGroup(RENDER_ALPHA, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CDoor::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CDoor::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();

	m_pAnimation->Render_Component();
	m_pRcTex->Render_Component();
}

void CDoor::OnCollisionEnter(const Collision * collsion)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (nullptr != pPlayer)
	{	
		_int iNextRoomIdx = 0;
		DOOR_DIR eNextDoor = DOOR_DIR_END;

		CRoom* pNextRoom = nullptr;
		CDoor* pNextDoor = nullptr;

		switch (m_eDir)
		{
		case Engine::DOOR_NORTH:
			iNextRoomIdx = m_pRoom->Get_Room_Index() + 3;
			eNextDoor = DOOR_SOUTH;
			break;

		case Engine::DOOR_SOUTH:
			iNextRoomIdx = m_pRoom->Get_Room_Index() - 3;
			eNextDoor = DOOR_NORTH;
			break;

		case Engine::DOOR_WEST:
			iNextRoomIdx = m_pRoom->Get_Room_Index() - 1;
			eNextDoor = DOOR_EAST;
			break;

		case Engine::DOOR_EAST:
			iNextRoomIdx = m_pRoom->Get_Room_Index() + 1;
			eNextDoor = DOOR_WEST;
			break;
		}
		pNextRoom = ROOM_MGR->Get_Room(iNextRoomIdx);
		pNextDoor = pNextRoom->Get_Door(eNextDoor);

		m_pInTennel->Set_Door(this);
		m_pOutTennel->Set_Door(pNextDoor);

		// ���Ƿ� �߰���
		ROOM_MGR->Set_In_Tennel(true);

		_vec3 vLook = pPlayer->m_pTransform->m_vInfo[INFO_LOOK];
		vLook.Normalize();
		_float fAngle = vLook.Degree(_vec3(0.f, 0.f, -1.f));
		pPlayer->m_pTransform->m_vInfo[INFO_POS] = m_pInTennel->m_pTransform->m_vInfo[INFO_POS];
		/*cout << pPlayer->m_pTransform->m_vInfo[INFO_LOOK].x << ", "
			<< pPlayer->m_pTransform->m_vInfo[INFO_LOOK].y << ", "
			<< pPlayer->m_pTransform->m_vInfo[INFO_LOOK].z << ", " << endl;*/
		pPlayer->m_pTransform->Rot_Yaw(fAngle, 1.f);

		if (m_eDir == DOOR_WEST)
			pPlayer->m_pTransform->Rot_Yaw(180.f, 1.f);
	}
}

HRESULT CDoor::Add_Component()
{
	m_pRcTex = dynamic_cast<CRcTex*>(Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"RcTex", m_pRcTex });

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Dock_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"Dock_Texture", m_pTextureCom);

	m_pCollider = dynamic_cast<CCollider*>(Clone_Proto(L"Collider", L"Collider", this, COL_TRIGGER));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });
	m_pCollider->Set_BoundingBox({ 1.f, 4.f, 1.f });

	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);

	m_pAnimation->BindAnimation(ANIM_WALK, m_pTextureCom, 0.03f, false);
	m_pAnimation->SelectState(ANIM_WALK);
	m_pAnimation->ToggleInverse();
	m_uMapComponent[ID_UPDATE].insert({ L"Animation", m_pAnimation });

	return S_OK;
}

void CDoor::Set_Door_State()
{
	m_pTransform->m_vScale = { 3.f, 5.f, 1.f };

	_vec3 vPos(0.f, 0.f, 0.f);
	_vec3 vCurRoomPos = m_pRoom->m_pTransform->m_vInfo[INFO_POS];
	switch (m_eDir)
	{
	case Engine::DOOR_NORTH:
		vPos = { vCurRoomPos.x + 25.f, 3.f, vCurRoomPos.z + 50.f };
		m_pTransform->Rot_Yaw(180.f, 1.f);
		break;

	case Engine::DOOR_SOUTH:
		vPos = { vCurRoomPos.x + 25.f, 3.f, vCurRoomPos.z + 0.f };
		break;

	case Engine::DOOR_WEST:
		vPos = { vCurRoomPos.x + 0.f, 3.f, vCurRoomPos.z + 25.f };
		m_pTransform->Rot_Yaw(90.f, 1.f);
		break;

	case Engine::DOOR_EAST:
		vPos = { vCurRoomPos.x + 50.f, 3.f, vCurRoomPos.z + 25.f };
		m_pTransform->Rot_Yaw(270.f, 1.f);
		break;
	}
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Move_Walk(0.1f, 1.f);
}

CDoor * CDoor::Create(LPDIRECT3DDEVICE9 pGraphicDev, DOOR_DIR eDir, CRoom* pRoom)
{
	CDoor* pInstance = new CDoor(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(eDir, pRoom)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CDoor::Free(void)
{
	__super::Free();
}
