#include "ImInspector.h"
#include "ImManager.h"
#include "Export_Function.h"

#include "EditCamera.h"

#include "Room.h"
#include "RoomMgr.h"
#include "FileSystem.h"
#include "ImPickBox.h"
#include "ListBox.h"

// 몬스터 헤더파일
#include "Baller.h"
#include "Bub.h"
#include "Turret.h"
#include "Walker.h"
#include "Factory.h"
// 맵 오브젝트 헤더파일
#include "SoftPyramid.h"
#include "HardPyramid.h"
#include "Slider.h"
#include "TileFactory.h"
#include "MonsterFactory.h"
#include "MapObjectFactory.h"
#include "WallFactory.h"

CImInspector::CImInspector(LPDIRECT3DDEVICE9 pGraphicDev)
	: CImWindow(pGraphicDev)
	, m_pCurTarget(nullptr)
	, m_pCurRoom(nullptr)

{
	ZeroMemory(m_vObjectPos, sizeof(_vec3));
}

CImInspector::~CImInspector()
{
	for (auto& PickBox : m_pPickBox)
		Safe_Release(PickBox);
}

HRESULT CImInspector::Ready_ImWindow()
{
	items.push_back({ "Tile", TILE_FACTORY });
	items.push_back({ "Wall", WALL_FACTORY });
	items.push_back({ "Monster", MONSTER_FACTORY });
	items.push_back({ "MapObject", MAPOBJ_FACTORY });

	for (_int i = 0; i < items.size(); ++i)
	{
		m_pPickBox[i] = CImPickBox::Create(m_pGraphicDev, items[i].first, items[i].second);
	}

	// 오브젝트 리스트
	//ROOM_MGR->Get_CurRoom()->
	//m_pObjListBox = ListBox::Create(m_pGraphicDev, , "Object List in Room");
	return S_OK;
}

_int CImInspector::Update(float fTimeDelta)
{
	if (!IsEnable())
		return 0;

	m_pCamera = dynamic_cast<CEditCamera*>(Get_GameObject(LAYER_CAMERA, L"Edit_Camera"));

	ImGui::Begin("Inspector");

	if (ImGui::CollapsingHeader("RommInfo"))
		Show_RoomInfo();

	if (ImGui::CollapsingHeader("PlaceMode"))
		Show_PlaceMode();

	if (ImGui::CollapsingHeader("ObjectList"))
		Show_MonsterList();

	if(ImGui::CollapsingHeader("Components"))
		Show_Components();

	ImGui::End();

	return 0;
}

void CImInspector::Show_RoomInfo()
{
	/*const char* items[25] = { "0", "1", "2", "3", "4",
		"5", "6", "7", "8", "9",
		"10", "11", "12", "13", "14",
		"15", "16", "17", "18", "19",
		"20", "21", "22", "23", "24" };*/
	const char* items[9] = { "0", "1", "2", "3", "4",
		"5", "6", "7", "8" };
	static int item_current = 0;
	ImGui::Combo("Room_Index", &item_current, items, IM_ARRAYSIZE(items));

	m_vObjectPos.x = _float(item_current % 3 * 60 + 5);
	m_vObjectPos.y = 5.f;
	m_vObjectPos.z = _float(item_current / 3 * 60 + 5);

	m_pCamera->m_pTransform->m_vInfo[INFO_POS] = { m_vObjectPos.x + 25.f, 25.f, m_vObjectPos.z + 25.f };
	ROOM_MGR->Set_CurRoom(item_current);
	m_pCurRoom = ROOM_MGR->Get_CurRoom();

	static _int iObjNum = 0, iPre = 0;

	ImGui::RadioButton("DOOR_ES", &iObjNum, 0); ImGui::SameLine();
	ImGui::RadioButton("DOOR_ESW", &iObjNum, 1); ImGui::SameLine();
	ImGui::RadioButton("DOOR_EW", &iObjNum, 2);
	ImGui::RadioButton("DOOR_N", &iObjNum, 3); ImGui::SameLine();
	ImGui::RadioButton("DOOR_NE", &iObjNum, 4);
	ImGui::RadioButton("DOOR_NES", &iObjNum, 5); ImGui::SameLine();
	ImGui::RadioButton("DOOR_NESW", &iObjNum, 6); ImGui::SameLine();
	ImGui::RadioButton("DOOR_NS", &iObjNum, 7);
	ImGui::RadioButton("DOOR_NW", &iObjNum, 8); ImGui::SameLine();
	ImGui::RadioButton("DOOR_S", &iObjNum, 9);
	ImGui::RadioButton("DOOR_SW", &iObjNum, 10); ImGui::SameLine();
	ImGui::RadioButton("DOOR_SWN", &iObjNum, 11); ImGui::SameLine();
	ImGui::RadioButton("DOOR_W", &iObjNum, 12);
	ImGui::RadioButton("DOOR_WNE", &iObjNum, 13); ImGui::SameLine();
	ImGui::RadioButton("DOOR_E", &iObjNum, 14);

	if (iPre != iObjNum)
	{
		m_pCurRoom->Set_DoorType((DOOR_TYPE)iObjNum);
		iPre = iObjNum;
	}
}

void CImInspector::Show_Components()
{
	if (nullptr == m_pCurTarget)
		return;

	auto uMapComponent = m_pCurTarget->Get_ComponentMap();

	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter : uMapComponent[i])
		{
			if (CTransform* pTrans = dynamic_cast<CTransform*>(iter.second))
			{
				if (ImGui::TreeNode("Transform"))
				{
					ImGui::SeparatorText("Info_Pos");

					ImGui::DragFloat("Pos_X", &pTrans->m_vInfo[INFO_POS].x, 0.01f);
					ImGui::DragFloat("Pos_Y", &pTrans->m_vInfo[INFO_POS].y, 0.01f);
					ImGui::DragFloat("Pos_Z", &pTrans->m_vInfo[INFO_POS].z, 0.01f);

					ImGui::SeparatorText("Info_Rotation");

					static _float fAngleX = 0.f;
					static _float fAngleY = 0.f;
					static _float fAngleZ = 0.f;

					ImGui::DragFloat("Rot_X", &fAngleX, 0.1f);
					ImGui::DragFloat("Rot_Y", &fAngleY, 0.1f);
					ImGui::DragFloat("Rot_Z", &fAngleZ, 0.1f);

					pTrans->m_vInfo[INFO_RIGHT] =	{ 1.f, 0.f, 0.f };
					pTrans->m_vInfo[INFO_UP]	=	{ 0.f, 1.f, 0.f };
					pTrans->m_vInfo[INFO_LOOK]	=	{ 0.f, 0.f, 1.f };

					pTrans->Rot_Pitch(fAngleX, 1.f);
					pTrans->Rot_Yaw(fAngleY, 1.f);
					pTrans->Rot_Roll(fAngleZ, 1.f);

					ImGui::SeparatorText("Info_Scale");

					ImGui::DragFloat("Scale_X", &pTrans->m_vScale.x, 0.01f);
					ImGui::DragFloat("Scale_Y", &pTrans->m_vScale.y, 0.01f);
					ImGui::DragFloat("Scale_Z", &pTrans->m_vScale.z, 0.01f);

					_float fAll = 0.f;
					ImGui::DragFloat("Scale_XYZ", &fAll, 0.01f);
					pTrans->m_vScale.x += fAll;
					pTrans->m_vScale.y += fAll;
					pTrans->m_vScale.z += fAll;

					ImGui::TreePop();
					ImGui::Spacing();
				}
			}

			if (CCollider* pCollider = dynamic_cast<CCollider*>(iter.second))
			{
				char* p = (char*)iter.first;

				if (ImGui::TreeNode(p))
				{
					if (false == pCollider->Toggle_IsRender())
						pCollider->Toggle_IsRender();

					_float fLength = 0.f;
					_vec3 vBoundSize(0.f, 0.f, 0.f);

					ImGui::DragFloat("Len_X", &fLength, 0.01f);
					vBoundSize = pCollider->Get_BoundSize();
					pCollider->Set_BoundingBox({ vBoundSize.x + fLength, vBoundSize.y, vBoundSize.z });

					fLength = 0.f;
					ImGui::DragFloat("Len_Y", &fLength, 0.01f);
					vBoundSize = pCollider->Get_BoundSize();
					pCollider->Set_BoundingBox({ vBoundSize.x, vBoundSize.y + fLength, vBoundSize.z });

					fLength = 0.f;
					ImGui::DragFloat("Len_Z", &fLength, 0.01f);
					vBoundSize = pCollider->Get_BoundSize();
					pCollider->Set_BoundingBox({ vBoundSize.x, vBoundSize.y, vBoundSize.z + fLength });

					fLength = 0.f;
					ImGui::DragFloat("Len_XYZ", &fLength, 0.01f);
					vBoundSize = pCollider->Get_BoundSize();
					pCollider->Set_BoundingBox({ vBoundSize.x + fLength, vBoundSize.y + fLength, vBoundSize.z + fLength });

					ImGui::TreePop();
					ImGui::Spacing();
				}
				else if(true == pCollider->Toggle_IsRender())
					pCollider->Toggle_IsRender();
			}
			if (dynamic_cast<CCamera*>(iter.second))
			{
				if (ImGui::TreeNode("Camera"))
				{
					ImGui::Text("Camera");
					ImGui::TreePop();
					ImGui::Spacing();
				}
			}
		}
	}
}

void CImInspector::Show_PlaceMode()
{
	for (_int i = 0; i < PICK_END; ++i)
	{
		ImGui::RadioButton(items[i].first.c_str(), &m_iCurPickType, i);
		if(PICK_END - 1 != i) ImGui::SameLine();
	}
	m_pPickBox[m_iCurPickType]->Update(1.f);
	m_CurTag = TO_WSTR(m_pPickBox[m_iCurPickType]->Get_CurItem());

	if (PICK_MAPOBJ == m_iCurPickType)
	{
		ImGui::RadioButton("None", &m_radio, 0);
		ImGui::RadioButton("LeftUp", &m_radio, 1); ImGui::SameLine();
		ImGui::RadioButton("RightUp", &m_radio, 2); 
		ImGui::RadioButton("LeftDown", &m_radio, 3); ImGui::SameLine();
		ImGui::RadioButton("RightDown", &m_radio, 4);
	}
}


void CImInspector::Show_MonsterList()
{
	


}

CImInspector * CImInspector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CImInspector* pInstance = new CImInspector(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CImInspector::Free(void)
{
	__super::Free();
}
