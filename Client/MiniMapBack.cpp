#include "MiniMapBack.h"
#include "Export_Function.h"
#include "RoomMgr.h"

CMiniMapBack::CMiniMapBack(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
	, m_curStageInfo(STAGE1)
{
	Set_ObjTag(L"MiniMapBack");
}

CMiniMapBack::~CMiniMapBack()
{
}

HRESULT CMiniMapBack::Add_Component()
{
	for (size_t i = 0; i < m_arrMap.size(); i++)
	{
		m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
		m_arrMap[i] = m_pRcTex;
		//m_uMapComponent[ID_RENDER].insert({ L"RcTex", m_arrMap[i] });
	} 

	m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"MiniMapBack_Texture", this));
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"MiniMapBack_Texture", m_pTexture });

	return S_OK;
}

HRESULT CMiniMapBack::Ready_GameObject(void)
{
	if (Engine::Get_Player() != nullptr)
	{
		m_pPlayerX = Engine::Get_Player()->m_pTransform->m_vInfo[INFO_POS].x;
		m_pPlayerZ = Engine::Get_Player()->m_pTransform->m_vInfo[INFO_POS].z;
	}

	m_vScale = { 24.f, 24.f , 0.f };

	m_arrMapInfo[0].m_iTextureNum = 4;
	m_arrMapInfo[1].m_iTextureNum = 2;
	m_arrMapInfo[2].m_iTextureNum = 8;
	m_arrMapInfo[3].m_iTextureNum = 7;
	m_arrMapInfo[4].m_iTextureNum = 3;
	m_arrMapInfo[5].m_iTextureNum = 7;
	m_arrMapInfo[6].m_iTextureNum = 0;
	m_arrMapInfo[7].m_iTextureNum = 1;
	m_arrMapInfo[8].m_iTextureNum = 10;



	__super::Ready_GameObject();

	return S_OK;
}

_int CMiniMapBack::Update_GameObject(const _float & fTimeDelta)
{
	if (m_curStageInfo != ROOM_MGR->Get_CurStageInfo())
	{
		MiniMapReset();
		m_curStageInfo = ROOM_MGR->Get_CurStageInfo();
	}
	
	Engine::Add_RenderGroup(RENDER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CMiniMapBack::LateUpdate_GameObject(void)
{
	if (m_bLevelUp == true)
	{
		MiniMapReset();
		m_bLevelUp = false;
	}
	MiniMapMove();
	MiniMapCheck();
	MiniMapInRange();
	__super::LateUpdate_GameObject();
}

void CMiniMapBack::Render_GameObject(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	m_pGraphicDev->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	m_pGraphicDev->SetRenderState(D3DRS_STENCILREF, 1);
	m_pGraphicDev->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	m_pGraphicDev->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	m_pGraphicDev->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

	CUI::Set_ViewMatrix_UI(320.f, -200.f, 75.0f, 85.f);
	m_pTexture->Render_Texture(15);
	m_pRcTex->Render_Component();

	m_pGraphicDev->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	m_pGraphicDev->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	CUI::Set_ViewMatrix_UI(320. + 50, -200 + 50, 200.f, 200.f);
	m_pTexture->Render_Texture(17);
	m_pRcTex->Render_Component();

	for (size_t i = 0; i < ROOMY; i++)
	{
		for (size_t j = 0; j < ROOMX; j++)
		{
			if (m_arrMapInfo[i * ROOMY + j].m_bCheck == true)
			{
				CUI::Set_ViewMatrix_UI(m_fPosX + j * 48, m_fPosY + i * 48, m_vScale.x, m_vScale.y);
				m_pTexture->Render_Texture(m_arrMapInfo[i * ROOMY + j].m_iTextureNum);
				m_arrMap[i * ROOMY + j]->Render_Component();
			}
			else if (m_arrMapInfo[i * ROOMY + j].m_bInRange == true)
			{
				CUI::Set_ViewMatrix_UI(m_fPosX + j * 48, m_fPosY + i * 48, m_vScale.x, m_vScale.y);
				m_pTexture->Render_Texture(16);
				m_arrMap[i * ROOMY + j]->Render_Component();
			}
			else
			{
				CUI::Set_ViewMatrix_UI(m_fPosX + j * 48, m_fPosY + i * 48, m_vScale.x, m_vScale.y);
				m_pTexture->Render_Texture(15);
				m_arrMap[i * ROOMY + j]->Render_Component();
			}
		}
	}

	__super::Render_GameObject();
	m_pGraphicDev->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}



void CMiniMapBack::MiniMapReset()
{
	for (size_t i = 0; i < ROOMY; i++)
	{
		for (size_t j = 0; j < ROOMX; j++)
		{
			m_arrMapInfo[i * ROOMY + j].m_bCheck = false;
			m_arrMapInfo[i * ROOMY + j].m_bInRange = false;
		}
	}
}

void CMiniMapBack::MiniMapMove()
{
	if (Engine::Get_Player() != nullptr)
	{
		if (ROOM_MGR->Is_In_Tennel())
		{
			m_fPosX = -(m_pPlayerMoveX / 1.180555f) + 337.f;
			m_fPosY = -(m_pPlayerMoveZ / 1.180555f) - 190.f;
		}
		else
		{
			m_pPlayerMoveX = Engine::Get_Player()->m_pTransform->m_vInfo[INFO_POS].x;
			m_pPlayerMoveZ = Engine::Get_Player()->m_pTransform->m_vInfo[INFO_POS].z;


			if (m_pPlayerMoveZ > 120.f)
			{
				m_pPlayerMoveZ = m_pPlayerMoveZ - 17.f;
			}
			else if (m_pPlayerMoveX > 120.f)
			{
				m_pPlayerMoveX = m_pPlayerMoveX - 13.0f;
			}
			else if (m_pPlayerMoveZ > 60.f)
			{
				m_pPlayerMoveZ = m_pPlayerMoveZ - 10.f;
			}		
			if (m_pPlayerMoveX > 60.f)
			{
				m_pPlayerMoveX = m_pPlayerMoveX - 6.f;
			}

			m_fPosX = -(m_pPlayerMoveX / 1.180555f) + 337.f;
			m_fPosY = -(m_pPlayerMoveZ / 1.180555f) - 190.f;
			 
		}
	}
}

void CMiniMapBack::MiniMapCheck()
{
	if (CRoomMgr::GetInstance()->Get_CurRoom() == nullptr) {return;}
	CRoom* pCurRoom = CRoomMgr::GetInstance()->Get_CurRoom();
	_int iRoomIndex = pCurRoom->Get_Room_Index();

	for (size_t i = 0; i < ROOMX * ROOMY; i++)
	{
		if (i == iRoomIndex)
		{
			m_arrMapInfo[i].m_bCheck = true;
		}
	}
}

void CMiniMapBack::MiniMapInRange()
{
	if (CRoomMgr::GetInstance()->Get_CurRoom() == nullptr) { return; }
	CRoom* pCurRoom = CRoomMgr::GetInstance()->Get_CurRoom();
	_int iRoomIndex = pCurRoom->Get_Room_Index();

	switch (pCurRoom->Get_DoorType())
	{
	case DOOR_ES:
		m_arrMapInfo[iRoomIndex + 1].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 3].m_bInRange = true;
		break;
	case DOOR_ESW:
		m_arrMapInfo[iRoomIndex + 1].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 1].m_bInRange = true;
		break;
	case DOOR_EW:
		m_arrMapInfo[iRoomIndex + 1].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 1].m_bInRange = true;
		break;
	case DOOR_N:
		m_arrMapInfo[iRoomIndex + 3].m_bInRange = true;
		break;
	case DOOR_NE:
		m_arrMapInfo[iRoomIndex + 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex + 1].m_bInRange = true;
		break;
	case DOOR_NES:
		m_arrMapInfo[iRoomIndex + 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex + 1].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 3].m_bInRange = true;
		break;
	case DOOR_NESW:
		m_arrMapInfo[iRoomIndex + 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex + 1].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 1].m_bInRange = true;
		break;
	case DOOR_NS:
		m_arrMapInfo[iRoomIndex + 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 3].m_bInRange = true;
		break;
	case DOOR_NW:
		m_arrMapInfo[iRoomIndex + 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 1].m_bInRange = true;
		break;
	case DOOR_S:
		m_arrMapInfo[iRoomIndex - 3].m_bInRange = true;
		break;
	case DOOR_SW:
		m_arrMapInfo[iRoomIndex - 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 1].m_bInRange = true;
		break;
	case DOOR_SWN:
		m_arrMapInfo[iRoomIndex - 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex - 1].m_bInRange = true;
		m_arrMapInfo[iRoomIndex + 3].m_bInRange = true;
		break;
	case DOOR_W:
		m_arrMapInfo[iRoomIndex - 1].m_bInRange = true;
		break;
	case DOOR_WNE:
		m_arrMapInfo[iRoomIndex - 1].m_bInRange = true;
		m_arrMapInfo[iRoomIndex + 3].m_bInRange = true;
		m_arrMapInfo[iRoomIndex + 1].m_bInRange = true;
		break;
	case DOOR_E:
		m_arrMapInfo[iRoomIndex + 1].m_bInRange = true;
		break;
	}

}

CMiniMapBack * CMiniMapBack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMiniMapBack* pInstance = new CMiniMapBack(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMiniMapBack::Free(void)
{
	auto iter = m_arrMap.begin();
	for (; iter < m_arrMap.end(); iter++)
	{
		Safe_Release(*iter);
	}

	Safe_Release(m_pRcTex);
	Safe_Release(m_pTexture);

	__super::Free();
}


void CMiniMapBack::Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, scaleX, scaleY, 0.f);
	matTrans.Translation(posX, posY, 0.1f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}