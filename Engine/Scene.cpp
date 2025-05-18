#include "stdafx.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"

#include "Export_Function.h"
#include "SoundMgr.h"

CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bNextStage(false)
	, m_bEnding(false)
{
	m_pGraphicDev->AddRef();

	m_DynamicLayerArr.resize(LAYER_DYNAMIC_END - LAYER_STATIC_END - 1);
	for (int i = 0; i < LAYER_DYNAMIC_END - LAYER_STATIC_END - 1; i++)
	{
		m_DynamicLayerArr[i] = CLayer::Create();
	}

	m_SlowTime = 0.f;
}

CScene::~CScene()
{
}

CComponent * CScene::Get_Component(LAYERID LayerID, const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	return Get_Layer(LayerID)->Get_Component(pObjTag, pComponentTag, eID);
}

HRESULT CScene::Ready_Scene(void)
{
	_float fps60 = Engine::Get_Timer(L"Timer_FPS60");
	m_SlowTime = fps60;

	return S_OK;
}

_int CScene::Update_Scene(const _float & fTimeDelta)
{
	_int iResult = 0;

	for (int i = 0; i < LAYER_DYNAMIC_END; i++)
	{
		CLayer* curLayer = Get_Layer((LAYERID)i);
		if (curLayer == nullptr) continue;

		if (Engine::Key_Pressing(DIK_LSHIFT))
		{
			Play_SlowTime(fTimeDelta);
		}
		else if(Engine::Key_Up(DIK_LSHIFT))
		{
			if (CManagement::GetInstance()->Get_TimeStopped() == true)
				Reset_SlowTime(fTimeDelta);

			CManagement::GetInstance()->Set_TimeStopped(false);	
		}

		if (i == LAYER_PLAYER || i == LAYER_UI)
			iResult = curLayer->Update_Layer(fTimeDelta);
		else
		{
			iResult = curLayer->Update_Layer(m_SlowTime);
		}
		
			
		if (iResult & 0x80000000)
			return iResult;
	}
	
	return iResult;
}

void CScene::LateUpdate_Scene(void)
{
	for (int i = 0; i < LAYER_DYNAMIC_END; i++)
	{
		CLayer* curLayer = Get_Layer((LAYERID)i);
		if (curLayer == nullptr) continue;

		curLayer->LateUpdate_Layer();
	}	
}

void CScene::Remove_GameObject(LAYERID layerID, CGameObject* obj)
{
	if (layerID > LAYER_STATIC_END || layerID < 0) return;

	(*m_StaticLayerArr)[layerID]->Remove_GameObject(obj);
}

void CScene::Reset_Scene()
{
	CGameObject* player = Get_Player();
	if (player == nullptr) return;


	/*m_pTransform->m_vInfo[INFO_POS] = { 20.f,4.f,20.f };
	m_pTransform->m_vInfo[INFO_LOOK] = { 0.f, 0.f, 1.f };*/
	player->m_pTransform->m_vInfo[INFO_POS] = { 20.f,4.f,20.f };

	player->m_pTransform->Set_Dir({ 0.f,0.f,1.f });
	//player->m_pTransform->m_vInfo[INFO_LOOK] = { 0.f, 0.f, 1.f };
}

void Engine::CScene::Set_StaticLayerArr(vector<CLayer*>* layerArr)
{
	m_StaticLayerArr = layerArr;
}

HRESULT CScene::Add_GameObject(CGameObject* pObj)
{
	CLayer* curLayer = Get_Layer(pObj->Get_LayerID());
	if (curLayer == nullptr) return S_OK;

	FAILED_CHECK_RETURN(curLayer->Add_GameObject(pObj->Get_ObjTag(), pObj), E_FAIL);
		
	return S_OK;
}

CGameObject * CScene::Get_GameObject(LAYERID LayerID, const _tchar * pObjTag)
{
	CLayer* curLayer = Get_Layer(LayerID);
	if (curLayer == nullptr) nullptr;

	return curLayer->Get_GameObject(pObjTag);
}

void CScene::Play_SlowTime(const _float & fTimeDelta)
{
	m_SlowTime -= 0.0005f * fTimeDelta;

	if (m_SlowTime >= fTimeDelta - 0.005f)
		PLAY_SOUND(L"sfxBootDown.wav", SOUND_ENVIRONMENT, 1.f);

	if (m_SlowTime < 0.f) m_SlowTime = 0.f;

	if (m_SlowTime == 0.f) CManagement::GetInstance()->Set_TimeStopped();
	

	if (!IS_PLAYING(SOUND_BGM))
	{
		CSoundMgr::GetInstance()->SetVolumeCurBGM(0.01f);
		PLAY_BGM(L"SlowMotion.wav", SOUND_BGM, 1.f);
	}
		
}

void CScene::Reset_SlowTime(const _float & fTimeDelta)
{
	CSoundMgr::GetInstance()->StopCurBGM();
	CSoundMgr::GetInstance()->SetVolumePrevBGM(BGM_SOUND_VOLUME, true);
	
	m_SlowTime = fTimeDelta;
}

CLayer* CScene::Get_Layer(LAYERID LayerID)
{
	if (LayerID < LAYER_STATIC_END)
	{
		if (m_StaticLayerArr == nullptr) return nullptr;

		return (*m_StaticLayerArr)[LayerID];
	}
	else if (LayerID < LAYER_DYNAMIC_END)
	{
		if (LayerID == LAYER_STATIC_END) return nullptr;

		return m_DynamicLayerArr[LayerID - LAYER_STATIC_END - 1];
	}
}

void Engine::CScene::Free(void)
{
	for_each(m_DynamicLayerArr.begin(), m_DynamicLayerArr.end(), CDeleteObj());
	Safe_Release(m_pGraphicDev);
}
