#include "Logo.h"

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
#include "LoadingScene.h"


CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene(void)
{
	m_SlowTime = 0.016;

	FAILED_CHECK_RETURN(Ready_Proto(), E_FAIL);

	m_pBackGround = CBackGround::Create(m_pGraphicDev);
	Add_GameObject(m_pBackGround);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);


	//STOP_ALL_SOUND;
	//PLAY_BGM(L"Title.wav", SOUND_BGM, 0.5f);

	/*m_pLoading = CLoading::Create(m_pGraphicDev, LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);*/
	
	return S_OK;
}

_int CLogo::Update_Scene(const _float & fTimeDelta)
{
	int iExit = __super::Update_Scene(fTimeDelta);

	if (m_pBackGround->Get_GameMode() == GAMEMODE_NOCHOICE) return 0;
	if (m_pBackGround->Get_GameMode() == GAMEMODE_EXITGAME)
	{
		DestroyWindow(g_hWnd);
		return -1;
	}

	if (m_pBackGround->Selected_GameMode())
	{
		if (m_pBackGround->Get_GameMode() == GAMEMODE_EDITOR)
		{
			Start_WorldTimer();
			CScene* nextLoadingScene = CLoadingScene::Create(m_pGraphicDev, LOADING_EDITSTAGE);
			FAILED_CHECK_RETURN(Engine::Set_Scene(nextLoadingScene), E_FAIL);
		}
		else if (m_pBackGround->Get_GameMode() == GAMEMODE_STARTGAME)
		{
			CScene* nextLoadingScene = CLoadingScene::Create(m_pGraphicDev, LOADING_STAGE);

			Start_WorldTimer();
			FAILED_CHECK_RETURN(Engine::Set_Scene(nextLoadingScene, true), E_FAIL);
		}	
	}	

	return iExit;
}

void CLogo::LateUpdate_Scene(void)
{
	__super::LateUpdate_Scene();
}

void CLogo::Render_Scene(void)
{

}

HRESULT CLogo::Ready_Proto(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcTex", CRcTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Logo_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Logo/title3D.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Background_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Logo/BackGround.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"StarBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/Star_%d.png",4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SelectArrow_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/SelectArrow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Num_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Text/tigl_font2_DEPRECATE_%d.png", 42)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Animation", CAnimation::Create(m_pGraphicDev)), E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Transform", CTransform::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcTex_Dynamic", CRcTex::Create(m_pGraphicDev, VB_DYNAMIC)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Collider", CCollider::Create(m_pGraphicDev)), E_FAIL);
  
  ////////////////////////////////////////////////////////// 
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SonicWalk_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/Sonic_Walk_%d.png", 8)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SonicRun_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/Sonic_Run_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SonicDead_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/Sonic_Dead.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Cactus_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/Cactus%d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BigCactus_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/BigCactus%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Score_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/Score%d.png", 10)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Bird_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/Bird%d.png", 2)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Cloud_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/Cloud.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Gameover_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/GameOver.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Ground_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/Ground.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HI_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sonic/HI.png")), E_FAIL);
	////////////////////////////////////////////////////////////

	

	return S_OK;
}

CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo *	pInstance = new CLogo(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLogo::Free(void)
{
	Safe_Release(m_pBackGround);
	__super::Free();
}