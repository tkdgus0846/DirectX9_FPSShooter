#include "LoadingScene.h"

#include "Export_Function.h"
#include "BackGround.h"
#include "Stage.h"
#include "MyEdit.h"
#include "FileSystem.h"
#include "RoomMgr.h"
#include "Loading.h"
#include "..\Engine\SoundMgr.h"

#include "TileFactory.h"
#include "MonsterFactory.h"
#include "MapObjectFactory.h"
#include "..\Engine\Management.h"

#include "MiniGame.h"
#include "SonicGame.h"
#include "LoadingBackground.h"
#include "Portal.h"


CLoadingScene::CLoadingScene(LPDIRECT3DDEVICE9 pGraphicDev) :
	CScene(pGraphicDev),
	m_pLoadingBackground(nullptr),
	m_fLoadingTime(0.f)
{
}

CLoadingScene::~CLoadingScene()
{
}

HRESULT CLoadingScene::Ready_Scene(void)
{
	FAILED_CHECK_RETURN(Ready_Proto(), E_FAIL);

	m_bLoadingCreated = false;
	m_pLoading = CLoading::Create(m_pGraphicDev, m_eLoadingID);

	m_pLoadingBackground = CLoadingBackground::Create(m_pGraphicDev);
	Add_GameObject(m_pLoadingBackground);

	STOP_ALL_BGM;
	PLAY_BGM(L"SectorA.wav", SOUND_BGM, 0.4f);

	CManagement::GetInstance()->Reset_WorldTime();
	switch (m_eLoadingID)
	{
	case LOADING_STAGE:
		m_pMiniGame = CSonicGame::Create(m_pGraphicDev);
		break;
	case LOADING_STAGE2:
		m_pMiniGame = CSonicGame::Create(m_pGraphicDev);
		break;
	case LOADING_STAGE3:
		m_pMiniGame = CSonicGame::Create(m_pGraphicDev);
		break;
	case LOADING_STAGE4:
		m_pMiniGame = CSonicGame::Create(m_pGraphicDev);
		break;
	default:
		break;

	}
	


	return S_OK;
}

_int CLoadingScene::Update_Scene(const _float & fTimeDelta)
{
	_int exitNum = 0;

	if (m_pMiniGame != nullptr)
		exitNum = m_pMiniGame->Update_Scene(fTimeDelta);


	if (m_pLoading->Get_Finish() == false)
	{
		if (m_pLoadingBackground != nullptr)
		{
			m_pLoadingBackground->Update_GameObject(fTimeDelta);
			m_fLoadingTime += fTimeDelta;

			if (m_fLoadingTime > 0.5f)
			{
				m_pLoadingBackground->Loading_Next_Text();
				m_fLoadingTime = 0.f;
			}
		}
	}	
	else
	{
		if (m_pLoadingBackground != nullptr)
		{
			m_pLoadingBackground->Update_GameObject(fTimeDelta);
			m_pLoadingBackground->Loading_Complete_Text();
		}
		
		if (Key_Down(DIK_RETURN))
		{
			switch (m_eLoadingID)
			{
			case LOADING_EDITSTAGE:
			{
				m_pScene = CMyEdit::Create(m_pGraphicDev);
				NULL_CHECK_RETURN(m_pScene, -1);

				m_pScene->Set_StaticLayerArr(ROOM_MGR->Get_CurLayerVec());

				for (int i = 0; i < COL_STATIC_END; i++)
				{
					CCollisionMgr::GetInstance()->Set_StaticColliderList(ROOM_MGR->Get_CurColliderList(i), i);
				}

				m_pScene->Update_Scene(fTimeDelta);
				FAILED_CHECK_RETURN(Engine::Set_Scene(m_pScene), E_FAIL);
				
				return 0;
			}
			break;
			case LOADING_STAGE:
			{
				m_pScene = CStage::Create(m_pGraphicDev);

				NULL_CHECK_RETURN(m_pScene, -1);

				m_pScene->Set_StaticLayerArr(ROOM_MGR->Get_CurLayerVec());

				for (int i = 0; i < COL_STATIC_END; i++)
				{
					CCollisionMgr::GetInstance()->Set_StaticColliderList(ROOM_MGR->Get_CurColliderList(i), i);
				}


				CManagement::GetInstance()->Reset_WorldTime();
				FAILED_CHECK_RETURN(Engine::Set_Scene(m_pScene), E_FAIL);
				return 0;
			}
			break;
			// Stage 2 3 4 �ε��ؼ� ��ȯ ���ִ� �κ�.
			default:
			{
				NULL_CHECK_RETURN(m_pScene, -1);
				STOP_ALL_BGM;
				if (m_eLoadingID == LOADING_STAGE2)
				{
					PLAY_BGM(L"Sector2.wav", SOUND_BGM_FIELD, BGM_SOUND_VOLUME);
					/*CPortal* portal = CPortal::Create(m_pGraphicDev, { 85.f, 4.f, 85.f});
					m_pScene->Add_GameObject(portal);*/
				}
				else if (m_eLoadingID == LOADING_STAGE3)
				{	
					PLAY_BGM(L"Sector3.wav", SOUND_BGM_FIELD, BGM_SOUND_VOLUME);
				}
				else if (m_eLoadingID == LOADING_STAGE4)
				{
					PLAY_BGM(L"Sector4.wav", SOUND_BGM_FIELD, BGM_SOUND_VOLUME);
				}

				m_pScene->Set_StaticLayerArr(ROOM_MGR->Get_CurLayerVec());
				m_pScene->Reset_Scene();

				for (int i = 0; i < COL_STATIC_END; i++)
				{
					CCollisionMgr::GetInstance()->Set_StaticColliderList(ROOM_MGR->Get_CurColliderList(i), i);
				}

				CManagement::GetInstance()->Reset_WorldTime();
				FAILED_CHECK_RETURN(Engine::Set_Scene(m_pScene), E_FAIL);
			}
			break;

			}
		}
		
	}
	return exitNum;
}

void CLoadingScene::LateUpdate_Scene(void)
{
	if (m_pMiniGame != nullptr)
		m_pMiniGame->LateUpdate_Scene();

	for (int i = LAYER_STATIC_END + 1; i < LAYER_DYNAMIC_END; i++)
	{
		CLayer* curLayer = Get_Layer((LAYERID)i);
		if (curLayer == nullptr) continue;

		curLayer->LateUpdate_Layer();
	}
}




void CLoadingScene::Render_Scene(void)
{
	// _DEBUG ?? ???	
	if (m_pLoading == nullptr) return;
	
	/*Engine::Render_Font(L"Font_Default", m_pLoading->Get_String(), &_vec2(20.f, 20.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));*/

}

HRESULT CLoadingScene::Ready_Proto(void)
{

	return S_OK;
}

CLoadingScene * CLoadingScene::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID loadingID, CScene* stageScene)
{
	CLoadingScene *	pInstance = new CLoadingScene(pGraphicDev);
	pInstance->Set_LoadingID(loadingID);

	pInstance->Set_Stage(stageScene);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLoadingScene::Free(void)
{
	//Safe_Release(m_pScene);
	Safe_Release(m_pLoading);
	Safe_Release(m_pMiniGame);
	__super::Free();
}