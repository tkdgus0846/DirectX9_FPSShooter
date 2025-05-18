#include "stdafx.h"
#include "RoomMgr.h"

#include "Tennel.h"
#include "Layer.h"
#include "Export_Function.h"

#include "NubBoss.h"
#include "WalkerBoss.h"
#include "TreeBoss.h"
#include "WormHead.h"
#include "WormBody.h"
#include "WormTail.h"
#include "Bub.h"
#include "Rub.h"
#include "Cryder.h"
#include "SoftPyramid.h"
#include "HardPyramid.h"
#include "Slider.h"
#include "Speyeder.h"
#include "ShopNpc.h"
#include  "OnlyCollisionObj.h"

IMPLEMENT_SINGLETON(CRoomMgr)

CRoomMgr::CRoomMgr()
	: m_pCurRoom(nullptr),
	m_bIsInTennel(false)
{
	for (int i = 0; i < 9; i++)
		m_arrRoom[i] = nullptr;

	m_pTennel[0] = nullptr;
	m_pTennel[1] = nullptr;
}

CRoomMgr::~CRoomMgr()
{
	Free();
}

HRESULT CRoomMgr::Ready_RoomMgr(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	m_pGraphicDev->AddRef();
	
	return S_OK;
}

void CRoomMgr::Release_All_Room()
{
	_int iIndex = 0;
	for (auto Room : m_arrRoom) // 방의 개수는 9 개. 콜리젼 그룹과 같지 않다.
	{
		CManagement::GetInstance()->Set_StaticLayerArr_Management(Room->GetLayerVec());
		for (int i = 0; i < COL_STATIC_END; i++)
		{
			CCollisionMgr::GetInstance()->Set_StaticColliderList(Room->GetColliderList(i), i);
		}
		Safe_Release(Room);

		
	}
	CCollisionMgr::GetInstance()->Clear_Static_ColliderList();
}

void CRoomMgr::Create_Default_Room(STAGEINFO stageInfo)
{
	DOOR_TYPE tmp[9] = 
	{	DOOR_NE, 
		DOOR_EW, 
		DOOR_NW,
		DOOR_NS,
		DOOR_N,
		DOOR_NS,
		DOOR_ES,
		DOOR_ESW,
		DOOR_SW
	};

	for (_uint i = 0; i < 3; ++i)
	{
		for (_uint j = 0; j < 3; ++j)
		{
			_uint iIndex = i * 3 + j;

			CRoom* pRoom = CRoom::Create(m_pGraphicDev, stageInfo);

			pRoom->m_pTransform->m_vInfo[INFO_POS] = { j * 60.01f, 0.f, i * 60.01f };
			pRoom->FloorSubSet();
			pRoom->PlaceSubSet();
			
			m_arrRoom[iIndex] = pRoom;
			m_arrRoom[iIndex]->Set_DoorType(tmp[iIndex]);
		}
	}

	m_pCurRoom = m_arrRoom[0];
}

void CRoomMgr::Push_Back_Obj(_int iIndex, CGameObject* pObj)
{
	m_arrRoom[iIndex]->PushBack_GameObj(pObj);
}

void CRoomMgr::Set_Tennel_Texture(STAGEINFO stageInfo)
{
	m_pTennel[0]->Set_Tennel_Texture(stageInfo);
	m_pTennel[1]->Set_Tennel_Texture(stageInfo);

}


void CRoomMgr::Set_CurRoom(const _uint iIndex)
{
	m_pCurRoom = m_arrRoom[iIndex];
}

void CRoomMgr::Set_Tennel(CTennel* tennel, _int iIndex)
{
	m_pTennel[iIndex] = tennel;

	if (iIndex == 0)
		tennel->m_pTransform->Rot_Yaw(180.f, 1.f);
}

STAGEINFO CRoomMgr::Get_CurStageInfo()
{
	if (m_pTennel[0] == nullptr) return STAGE1;
	return m_pTennel[0]->GetStageInfo();
}
_bool CRoomMgr::WriteMapFile(HANDLE hFile, DWORD& dwByte)
{
	_int iSize = m_arrRoom.size();
	WriteFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iSize; ++i)
	{
		m_arrRoom[i]->WriteRoomFile(hFile, dwByte);
	}
	return true;
}

_bool CRoomMgr::ReadMapFile(HANDLE hFile, DWORD& dwByte)
{
	_int iSize;
	ReadFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < 9; ++i)
	{
		m_arrRoom[i]->ReadRoomFile(hFile, dwByte);
		
		m_arrRoom[i]->FloorSubSet();
		m_arrRoom[i]->PlaceSubSet();
				
	}

	return true;
}

vector<CLayer*>* CRoomMgr::Get_CurLayerVec()
{
	return m_pCurRoom->GetLayerVec();
}

list<CCollider*>* CRoomMgr::Get_CurColliderList(_int iIndex)
{
	return m_pCurRoom->GetColliderList(iIndex);
}

void CRoomMgr::Free()
{
	for (auto Room : m_arrRoom)
	{
		if (Room == nullptr) continue;

		CManagement::GetInstance()->Set_StaticLayerArr_Management(Room->GetLayerVec());
		for (int i = 0; i < COL_STATIC_END; i++)
		{
			CCollisionMgr::GetInstance()->Set_StaticColliderList(Room->GetColliderList(i), i);
		}
		Safe_Release(Room);
	}
	Safe_Release(m_pGraphicDev);
}