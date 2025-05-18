#include "stdafx.h"
#include "CutSceneCamera.h"

#include "NubBoss.h"
#include "TreeBoss.h"
#include "WormHead.h"
#include "WalkerBoss.h"
#include "RoomMgr.h"
#include "Export_Function.h"
#include "CutSceneUI.h"
CCutSceneCamera::CCutSceneCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_fDegree(0.f), m_bIsDone(false)
	, m_fTime(0.f)
{
	Set_LayerID(LAYER_CAMERA);
	Set_ObjTag(L"CutScene_Camera");
}

CCutSceneCamera::~CCutSceneCamera()
{
}

HRESULT CCutSceneCamera::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_fDegree = 60.f;
	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(85.f, 4.f, 109.f);

	return result;
}

_int CCutSceneCamera::Update_GameObject(const _float & fTimeDelta)
{
	if (Get_WorldTime() < 5.f)
		m_bIsDone = false;

	if (false == m_bIsDone && ROOM_MGR->Get_CurRoom()->Get_Room_Index() == 4) // 컷씬이 진행 안됐고 보스방에 진입하면
	{
		On_Camera(L"CutScene_Camera");	// 카메라 컷씬으로 바꾸고

		if (CRenderer::GetInstance()->GetIsRenderUI() == true) // UI 다 끄고
			CRenderer::GetInstance()->ToggleRenderUI();

		vector<CGameObject*> pVec;
		CGameObject* pBoss = nullptr;

		Get_Layer(LAYER_BOSS)->Get_GameObject_ALL(&pVec);	// 보스레이어에 보스 확인한다음

		if (pVec.size())
			pBoss = pVec.front();

		if (pBoss == nullptr)
			return OBJ_NOEVENT;

		if (dynamic_cast<CNubBoss*>(pBoss))	// 현재 보스가 NubBoss이면
			Nub_CutScene(dynamic_cast<CNubBoss*>(pBoss));					// Nub컷씬 실행

		else if (dynamic_cast<CTreeBoss*>(pBoss))
			Tree_CutScene(dynamic_cast<CTreeBoss*>(pBoss));

		else if (dynamic_cast<CWormHead*>(pBoss))
			Worm_CutScene(dynamic_cast<CWormHead*>(pBoss));

		else if (dynamic_cast<CWalkerBoss*>(pBoss))
			Walker_CutScene(dynamic_cast<CWalkerBoss*>(pBoss));
	}

	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CCutSceneCamera::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCutSceneCamera::Render_GameObject(void)
{
}

HRESULT CCutSceneCamera::Add_Component(void)
{
	m_pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(m_pCamera, E_FAIL);
	m_uMapComponent[ID_UPDATE].emplace(L"CutScene_Camera", m_pCamera);
	m_pCamera->Set_CameraName(L"CutScene_Camera");

	return S_OK;
}

void CCutSceneCamera::Nub_CutScene(CNubBoss * pBoss)
{
	m_pTransform->m_vInfo[INFO_POS] = _vec3(85.f, 4.f, 109.f);
	_float fps60 = Get_Timer(L"Timer_FPS60");
	m_fTime += fps60;
	Add_GameObject(CCutSceneUI::Create(m_pGraphicDev));

	if (m_fTime > 4.f)
	{
		m_bIsDone = true;

		if (CRenderer::GetInstance()->GetIsRenderUI() == false)
			CRenderer::GetInstance()->ToggleRenderUI();


		Engine::Reset_SlowTime(fps60);
		On_Camera(L"Player_Camera");
		m_fDegree = 60.f;
		m_fTime = 0.f;
		return;
	}

	m_pTransform->m_vInfo[INFO_LOOK] = pBoss->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS];

	if (m_fTime > 2.1f)
	{
		if (m_fDegree < 30.f)
			m_fDegree = 30.f;

		m_pCamera->Set_FOV(m_fDegree);
		m_fDegree -= 0.5f;
	}
}

void CCutSceneCamera::Tree_CutScene(CTreeBoss * pBoss)
{
	m_pTransform->m_vInfo[INFO_POS] = _vec3(85.f, 4.f, 109.f);
	_float fps60 = Get_Timer(L"Timer_FPS60");
	m_fTime += fps60;

	if (m_fTime > 4.f)
	{
		m_bIsDone = true;

		if (CRenderer::GetInstance()->GetIsRenderUI() == false)
			CRenderer::GetInstance()->ToggleRenderUI();

		Engine::Reset_SlowTime(fps60);
		On_Camera(L"Player_Camera");
		m_fDegree = 60.f;
		m_fTime = 0.f;
		return;
	}

	m_pTransform->m_vInfo[INFO_LOOK] = pBoss->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS];
}

void CCutSceneCamera::Worm_CutScene(CWormHead * pBoss)
{
	m_pTransform->m_vInfo[INFO_POS] = _vec3(85.f, 4.f, 109.f);
	_float fps60 = Get_Timer(L"Timer_FPS60");
	m_fTime += fps60;
	Add_GameObject(CCutSceneUI::Create(m_pGraphicDev));

	if (m_fTime > 5.f)
	{
		m_bIsDone = true;

		if (CRenderer::GetInstance()->GetIsRenderUI() == false)
			CRenderer::GetInstance()->ToggleRenderUI();

		Engine::Reset_SlowTime(fps60);
		On_Camera(L"Player_Camera");
		m_fDegree = 60.f;
		m_fTime = 0.f;
		return;
	}

	m_pTransform->m_vInfo[INFO_LOOK] = Get_Player()->m_pTransform->m_vInfo[INFO_LOOK];
}

void CCutSceneCamera::Walker_CutScene(CWalkerBoss * pBoss)
{
	m_pTransform->m_vInfo[INFO_POS] = _vec3(85.f, 4.f, 100.f);
	_float fps60 = Get_Timer(L"Timer_FPS60");
	m_fTime += fps60;
	Add_GameObject(CCutSceneUI::Create(m_pGraphicDev));

	if (m_fTime > 5.f)
	{
		m_bIsDone = true;

		if (CRenderer::GetInstance()->GetIsRenderUI() == false)
			CRenderer::GetInstance()->ToggleRenderUI();

		Engine::Reset_SlowTime(fps60);
		On_Camera(L"Player_Camera");
		m_fDegree = 60.f;
		m_fTime = 0.f;
		return;
	}

	m_pTransform->m_vInfo[INFO_LOOK] = pBoss->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS];

}

CCutSceneCamera * CCutSceneCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCutSceneCamera* pInstance = new CCutSceneCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCutSceneCamera::Free()
{
	__super::Free();
}
