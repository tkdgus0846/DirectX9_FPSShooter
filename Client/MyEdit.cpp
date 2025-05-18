#include "MyEdit.h"

#include "ImManager.h"
#include "Monster.h"
#include "Bub.h"
#include "Baller.h"
#include "Walker.h"
#include "Turret.h"
#include "SkyBox.h"
#include "CutSceneCamera.h"
#include "EditCamera.h"
#include "Room.h"
#include "RoomMgr.h"
#include "ImManager.h"
#include "Export_Function.h"
#include "Tile.h"

#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"
#include "ImManager.h"
#include "FileSystem.h"
#include "..\Engine\SoundMgr.h"
CMyEdit::CMyEdit(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev), m_iCurRoomIdx(0)
	, m_iPreRoomIdx(0)
{
}

CMyEdit::~CMyEdit()
{
}

HRESULT CMyEdit::Ready_Scene(void)
{
	m_SlowTime = 0.016f;

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Camera", CCamera::Create(m_pGraphicDev)), E_FAIL);
	//Add_GameObject(LAYER_ENVIRONMENT, L"Map", CRoomMgr::Create(m_pGraphicDev));
	Add_GameObject(CSkyBox::Create(m_pGraphicDev));

	Add_GameObject(CEditCamera::Create(m_pGraphicDev));
	Engine::On_Camera(L"Edit_Camera");

	CImManager::GetInstance()->Ready_IMGUI(m_pGraphicDev);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

															  // Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(m_pGraphicDev);

	D3DLIGHT9		tLightInfo;
	ZeroMemory(&tLightInfo, sizeof(D3DLIGHT9));

	tLightInfo.Type = D3DLIGHT_DIRECTIONAL;
	tLightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Direction = _vec3(1.f, -1.f, 1.f);

	FAILED_CHECK_RETURN(Engine::Ready_Light(m_pGraphicDev, &tLightInfo, 0), E_FAIL);

	ShowCursor(TRUE);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	STOP_ALL_BGM;
	return S_OK;
}

_int CMyEdit::Update_Scene(const _float & fTimeDelta)
{
	CImManager::GetInstance()->Update(fTimeDelta);

	return __super::Update_Scene(fTimeDelta);
}

void CMyEdit::LateUpdate_Scene(void)
{
	__super::LateUpdate_Scene();

	m_iCurRoomIdx = ROOM_MGR->Get_CurRoom()->Get_Room_Index();

	if (m_iCurRoomIdx != m_iPreRoomIdx)
	{
		Set_StaticLayerArr(ROOM_MGR->Get_CurLayerVec());

		for (int i = 0; i < COL_STATIC_END; i++)
			CCollisionMgr::GetInstance()->Set_StaticColliderList(ROOM_MGR->Get_CurColliderList(i), i);

		m_iPreRoomIdx = m_iCurRoomIdx;
	}
}

void CMyEdit::Render_Scene(void)
{
	CImManager::GetInstance()->Render(m_pGraphicDev);
}

CMyEdit * CMyEdit::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMyEdit *	pInstance = new CMyEdit(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CMyEdit::Free(void)
{
	CImManager::DestroyInstance();
	__super::Free();
}
