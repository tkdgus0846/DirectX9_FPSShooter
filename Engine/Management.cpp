#include "stdafx.h"
#include "Export_Utility.h"
#include "Layer.h"
#include "Scene.h"

IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement() :
	m_pPlayer(nullptr),
	m_fWorldTime(0.f),
	m_bPlayingWorldTimer(false),
	m_bChangeRoom(false),
	m_bTimeStopped(false)
{
}

CManagement::~CManagement()
{
	Free();
}

CComponent * CManagement::Get_Component(LAYERID LayerID, const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	NULL_CHECK_RETURN(m_pScene, nullptr);
	return m_pScene->Get_Component(LayerID, pObjTag, pComponentTag, eID);
}

HRESULT CManagement::Set_Scene(CScene * pScene, _bool bChangingStage)
{
	Safe_Release(m_pScene);
	Engine::Clear_RenderGroup();

	m_pScene = pScene;

	m_bChangingStage = bChangingStage;

	return S_OK;
}

HRESULT CManagement::Set_Scene_NotDelete(CScene* pScene)
{
	Engine::Clear_RenderGroup();
	m_pScene = pScene;

	m_bChangingStage = true;

	return S_OK;
}

_int CManagement::Update_Management(const _float & fTimeDelta)
{
	NULL_CHECK_RETURN(m_pScene, -1);

	if (m_bPlayingWorldTimer)
	{
		m_fWorldTime += fTimeDelta;
	}
	
	return m_pScene->Update_Scene(fTimeDelta);
}

void CManagement::LateUpdate_Management()
{
	NULL_CHECK(m_pScene);
	m_pScene->LateUpdate_Scene();

	if (m_bChangeRoom == true)
	{
		m_bChangeRoom = false;
		return;
	}

	if (m_bChangingStage == true) 
	{
		Engine::Check_Collision(COL_PLAYER, COL_ENEMYBULLET);
		return;
	}

	if (m_bChangingStage == false)
	{
		Engine::Check_Collision(COL_PLAYERBULLET, COL_ENEMY);
		Engine::Check_Collision(COL_PLAYERBULLET, COL_DETECTION);
		Engine::Check_Collision(COL_PLAYERBULLET, COL_ENVIRONMENT);
		Engine::Check_Collision(COL_PLAYERBULLET, COL_OBJ);
		Engine::Check_Collision(COL_ENEMYBULLET, COL_PLAYER);
		Engine::Check_Collision(COL_ENEMYBULLET, COL_ENVIRONMENT);

		Engine::Check_Collision(COL_PLAYER, COL_OBJ);
		Engine::Check_Collision(COL_PLAYER, COL_ITEM);
		Engine::Check_Collision(COL_PLAYER, COL_TENNEL);
		Engine::Check_Collision(COL_PLAYER, COL_ENEMY);
		Engine::Check_Collision(COL_PLAYER, COL_DETECTION);
		Engine::Check_Collision(COL_PLAYER, COL_TRIGGER);
		Engine::Check_Collision(COL_PLAYER, COL_ENVIRONMENT);
		Engine::Check_Collision(COL_PLAYER, COL_ROOMITEM);
		/*Engine::Check_Collision(COL_TRIGGER, COL_PLAYERBULLET);*/

		Engine::Check_Collision(COL_ENEMY, COL_ENEMY);
		Engine::Check_Collision(COL_ENEMY, COL_ENVIRONMENT);
		Engine::Check_Collision(COL_ENEMY, COL_OBJ);

		Engine::Check_Collision(COL_OBJ, COL_TRIGGER);
		Engine::Check_Collision(COL_OBJ, COL_ENVIRONMENT);

		//////////////////////// debug
	}
}

void CManagement::Render_Management(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	NULL_CHECK(m_pScene);
	m_pScene->Render_Scene();
}

void CManagement::Add_GameObject(CGameObject * pObj)
{
	NULL_CHECK(pObj);

	m_pScene->Add_GameObject(pObj);	
}

CGameObject* CManagement::Get_GameObject(LAYERID LayerID, const _tchar * pObjTag)
{
	return m_pScene->Get_GameObject(LayerID, pObjTag);
}

void CManagement::Remove_GameObject(LAYERID layerID, CGameObject* obj)
{
	m_pScene->Remove_GameObject(layerID, obj);
}

void CManagement::Set_Player(CGameObject* player)
{
	if (m_pPlayer) MessageBox(NULL, L"�̹� �÷��̾ �����Ǿ� ����", L"System Message", MB_OK);
	m_pPlayer = player;
}

void CManagement::Stop_SlowTime()
{ 
	m_pScene->Stop_SlowTime();
}

void CManagement::Reset_SlowTime(const _float & fTimeDelta)
{
	m_pScene->Reset_SlowTime(fTimeDelta);
}

void CManagement::Set_StaticLayerArr_Management(vector<CLayer*>* layerArr)
{
	m_pScene->Set_StaticLayerArr(layerArr);
	m_bChangeRoom = true;
}

void CManagement::Next_Stage()
{
	m_pScene->Set_NextStage();
}


void CManagement::Set_Ending()
{
	m_pScene->Set_Ending();
}

void CManagement::Free(void)
{
	Safe_Release(m_pScene);
}
