#include "stdafx.h"
#include "Stage.h"

#include "Layer.h"
#include "Monster.h"
#include "Bub.h"
#include "Baller.h"
#include "Walker.h"
#include "Turret.h"
#include "SkyBox.h"
#include "CutSceneCamera.h"
#include "Room.h"
#include "RoomMgr.h"
#include "ImManager.h"
#include "Export_Function.h"
#include "GunUI.h"
#include "BulletBar.h"
#include "BulletGauge.h"
#include "CrossHair.h"
#include "Hp.h"
#include "Coin.h"
#include "Disc.h"
#include "WeaponType.h"
#include "MiniMap.h"
#include "MiniMapBack.h"
#include "BossHp.h"
#include "UltimateUI.h"
#include "SkillUI.h"
#include "PlayerHitUI.h"
#include "CutSceneUI.h"

#include "CoinItem.h"
#include "BulletItem.h"
#include "HeartItem.h"
#include "WeaponItem.h"
#include "DiscItem.h"
#include "Scope.h"

#include "Tennel.h"
#include "Pyramid.h"
#include "BootsItem.h"
#include "SoundMgr.h"
//#include "RenderTargetTest.h"

#include "ShopNpc.h"
#include "LoadingScene.h"
#include "EndingBackground.h"
CStage::CStage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev), m_iCurRoomIdx(0)
	, m_iPreRoomIdx(0)
{
}

CStage::~CStage()
{
}

HRESULT CStage::Ready_Scene(void)
{
	__super::Ready_Scene();
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Camera", CCamera::Create(m_pGraphicDev)), E_FAIL);

	m_StageInfo = LOADING_STAGE;
	
	/*Add_GameObject(LAYER_ENVIRONMENT, L"Room", CRoom::Create(m_pGraphicDev));
	dynamic_cast<CRoom*>(Get_GameObject(LAYER_ENVIRONMENT, L"Room"))->FloorSubSet();
	dynamic_cast<CRoom*>(Get_GameObject(LAYER_ENVIRONMENT, L"Room"))->PlaceSubSet();*/
	//Add_GameObject(LAYER_ENVIRONMENT, L"Map", CRoomMgr::Create(m_pGraphicDev));

	Add_GameObject(CSkyBox::Create(m_pGraphicDev));
	Add_GameObject(CPlayer::Create(m_pGraphicDev));

	/*Add_GameObject(LAYER_MONSTER, L"Monster_Baller", CBaller::Create(m_pGraphicDev));
	Add_GameObject(LAYER_MONSTER, L"Monster_Walker", CWalker::Create(m_pGraphicDev));*/
	//Add_GameObject(LAYER_MONSTER, L"Monster_Turret", CTurret::Create(m_pGraphicDev));
	//Add_GameObject(LAYER_MONSTER, L"Monster_Bub", CBub::Create(m_pGraphicDev, {1.f, 1.f, 1.f}));
	//Add_GameObject(LAYER_MONSTER, L"Monster_Bub", CBub::Create(m_pGraphicDev, {1.f, 1.f, 1.f}));
	//Add_GameObject(LAYER_MONSTER, L"Monster_Bub", CBub::Create(m_pGraphicDev, {1.f, 1.f, 1.f}));
	//Add_GameObject(LAYER_MONSTER, L"Monster_Bub", CBub::Create(m_pGraphicDev, {1.f, 1.f, 1.f}));
	/*Add_GameObject(LAYER_MONSTER, L"Monster_Guppi_Blue_Texture", CGuppi::Create(m_pGraphicDev));*/

	Add_GameObject(CCutSceneCamera::Create(m_pGraphicDev));	
	
	// UI
	Add_GameObject(CBulletGauge::Create(m_pGraphicDev));
	Add_GameObject(CBulletBar::Create(m_pGraphicDev));
	Add_GameObject(CBossHp::Create(m_pGraphicDev));
	Add_GameObject(CUltimateUI::Create(m_pGraphicDev));
	Add_GameObject(CSkillUI::Create(m_pGraphicDev));

	Add_GameObject(CCrossHair::Create(m_pGraphicDev));
	Add_GameObject(CHp::Create(m_pGraphicDev));
	Add_GameObject(CCoin::Create(m_pGraphicDev));
	Add_GameObject(CDisc::Create(m_pGraphicDev));
	Add_GameObject(CWeaponType::Create(m_pGraphicDev));
	Add_GameObject(CMiniMapBack::Create(m_pGraphicDev));
	Add_GameObject(CMiniMap::Create(m_pGraphicDev));
	Add_GameObject(CGunUI::Create(m_pGraphicDev));
	Add_GameObject(CScope::Create(m_pGraphicDev));

	Add_GameObject(CPlayerHitUI::Create(m_pGraphicDev));


	//Add_GameObject(CCutSceneUI::Create(m_pGraphicDev));

	// Tennel
	CTennel* tennel1 = CTennel::Create(m_pGraphicDev);
	CTennel* tennel2 = CTennel::Create(m_pGraphicDev);

	tennel1->Set_Position(0);
	tennel2->Set_Position(1);

	Add_GameObject(tennel1);
	Add_GameObject(tennel2);

	ROOM_MGR->Set_Tennel(tennel1, 0);
	ROOM_MGR->Set_Tennel(tennel2, 1);

	ROOM_MGR->Set_Tennel_Texture(STAGE1);

	// ���� �ʱ�ȭ
	D3DLIGHT9		tLightInfo;
	ZeroMemory(&tLightInfo, sizeof(D3DLIGHT9));
	tLightInfo.Type = D3DLIGHT_DIRECTIONAL;
	tLightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Direction = _vec3(0.f, -1.f, 0.f);

	FAILED_CHECK_RETURN(Engine::Ready_Light(m_pGraphicDev, &tLightInfo, 0), E_FAIL);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_pGraphicDev->SetRenderState(D3DRS_NORMALIZENORMALS, true); // ������� �ְ����

	STOP_ALL_BGM;
	PLAY_BGM(L"finalboss4.wav", SOUND_BGM_BOSS, BGM_SOUND_VOLUME);
	STOP_ALL_BGM;
	PLAY_BGM(L"Sector1.wav", SOUND_BGM_FIELD, BGM_SOUND_VOLUME);




	m_pEndingBackground = CEndingBackground::Create(m_pGraphicDev);

	return S_OK;
}

_int CStage::Update_Scene(const _float & fTimeDelta)
{
	//if (m_bNextStageCondition == true) return 0;
	if (m_bNextStage == true)
	{
		m_bNextStage = false;
		Next_Stage();
		return 0;
	}

	if (m_bEnding == true)
	{
		m_pEndingBackground->Update_GameObject(fTimeDelta);
	}

	if(0 == (*m_StaticLayerArr)[LAYER_MONSTER]->Get_ObjectSize() &&
		0 == (*m_StaticLayerArr)[LAYER_BOSS]->Get_ObjectSize())
		ROOM_MGR->Get_CurRoom()->Open_Doors();

	return __super::Update_Scene(fTimeDelta);
}

void CStage::LateUpdate_Scene(void)
{
	//if (m_bNextStageCondition == true) return;

	__super::LateUpdate_Scene();

	m_iCurRoomIdx = ROOM_MGR->Get_CurRoom()->Get_Room_Index();

	if (m_iCurRoomIdx != m_iPreRoomIdx)
	{
		CManagement::GetInstance()->Set_StaticLayerArr_Management(ROOM_MGR->Get_CurLayerVec());

		for (int i = 0; i < COL_STATIC_END; i++)
			CCollisionMgr::GetInstance()->Set_StaticColliderList(ROOM_MGR->Get_CurColliderList(i), i);

		m_iPreRoomIdx = m_iCurRoomIdx;
		ROOM_MGR->Get_CurRoom()->Close_Doors();
	}
}

void CStage::Render_Scene(void)
{
	if (m_bEnding == true)
	{
		m_pEndingBackground->Render_GameObject();
	}
}

void CStage::Next_Stage()
{
	m_StageInfo = (LOADINGID)((int)m_StageInfo + 1);
	CLoadingScene* loadingScene = CLoadingScene::Create(m_pGraphicDev, m_StageInfo, this);

	CManagement::GetInstance()->Set_Scene_NotDelete(loadingScene);
	//m_bNextStageCondition = true;
}

CStage * CStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStage *	pInstance = new CStage(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CStage::Free(void)
{
	Safe_Release(m_pEndingBackground);
	__super::Free();
}
