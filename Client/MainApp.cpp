//#include "stdafx.h"
#include "MainApp.h"
#include "Scene.h"
#include "Logo.h"
#include "BulletMgr.h"
#include "EffectManager.h"
#include "ImManager.h"
#include <time.h>

#include "Export_Function.h"
#include "RoomMgr.h"
#include "ParticleMgr.h"
#include "TileFactory.h"
#include "FileSystem.h"
#include "SoundMgr.h"
#include "MonsterFactory.h"
#include "MapObjectFactory.h"
#include "ItemManager.h"
#include "WallFactory.h"

// 주석 테스트용
CMainApp::CMainApp()
	: m_pDeviceClass(nullptr), m_pManagementClass(nullptr), m_pGraphicDev(nullptr)
{
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp(void)
{
	srand((unsigned int)time(NULL));
	FAILED_CHECK_RETURN(Ready_DefaultSetting(&m_pGraphicDev), E_FAIL);
	FAILED_CHECK_RETURN(Set_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL);


	//SECTION_MGR->Ready_SectionMgr(m_pGraphicDev);

	ROOM_MGR->Ready_RoomMgr(m_pGraphicDev);

	SOUND->Init();
	
	PLAY_BGM(L"Title.wav",SOUND_BGM, 1.f);
	return S_OK;
}

int CMainApp::Update_MainApp(const _float & fTimeDelta)
{
	Engine::Update_DInput();
	
	_long	dwMouse = 0;

	m_pManagementClass->Update_Management(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp(void)
{
	m_pManagementClass->LateUpdate_Management();
}

void CMainApp::Render_MainApp(void)
{
	Engine::Render_Begin(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.f));

	m_pManagementClass->Render_Management(m_pGraphicDev);

	Engine::Render_End();
}

HRESULT CMainApp::Ready_DefaultSetting(LPDIRECT3DDEVICE9 * ppGraphicDev)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);
	

	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Default", L"바탕", 15, 20, FW_HEAVY), E_FAIL);
	/*FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Jinji", L"궁서", 15, 20, FW_HEAVY), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Ganji", L"견고딕", 15, 20, FW_HEAVY), E_FAIL);*/

	// dinput
	FAILED_CHECK_RETURN(Engine::Ready_DInput(g_hInst, g_hWnd), E_FAIL);

	return S_OK;
}

HRESULT CMainApp::Set_Scene(LPDIRECT3DDEVICE9 pGraphicDev, CManagement ** ppManagement)
{
	CScene*		pScene = nullptr;
	pScene = CLogo::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Create_Management(ppManagement), E_FAIL);
	(*ppManagement)->AddRef();

	FAILED_CHECK_RETURN((*ppManagement)->Set_Scene(pScene), E_FAIL);

	return S_OK;
}

CMainApp * CMainApp::Create(void)
{
	CMainApp *	pInstance = new CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	
	return pInstance;
}

void CMainApp::Free(void)
{
	CTileFactory::DestroyInstance();
	CMonsterFactory::DestroyInstance();
	CMapObjectFactory::DestroyInstance();
	CWallFactory::DestroyInstance();
	CRoomMgr::DestroyInstance();
	CImManager::DestroyInstance();
	CBulletMgr::DestroyInstance();
	CParticleMgr::DestroyInstance();
	CEffectManager::DestroyInstance();
	CItemManager::DestroyInstance();
	CSoundMgr::DestroyInstance();

	
	// 룸 매니저에서 룸을 해제 하고 난뒤에 씬에서 해제하려면 문제가 있는가? 없음.

	Safe_Release(m_pGraphicDev);

	Safe_Release(m_pManagementClass);
	Safe_Release(m_pDeviceClass);

	Engine::Release_Utility();
	Engine::Release_System();
}
