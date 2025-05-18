#include "stdafx.h"
#include "Renderer.h"
#include "Export_Function.h"

IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer()
	:m_bRenderUI_Switch(true)
{
}

CRenderer::~CRenderer()
{
	Free();
}

void CRenderer::Add_RenderGroup(RENDERID eID, CGameObject * pGameObject)
{
	if (RENDER_END <= eID || nullptr == pGameObject)
		return;

	m_RenderGroup[eID].push_back(pGameObject);
	pGameObject->AddRef();
}

void CRenderer::Render_GameObject(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	DWORD prevColorOp, prevColorArg1;
	if (m_bColorInversion)
	{
		pGraphicDev->GetTextureStageState(0, D3DTSS_COLORARG1, &prevColorArg1);
		pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE | D3DTA_COMPLEMENT);
	}

	//----
	Render_Priority(pGraphicDev);
	Render_NonAlpha(pGraphicDev);
	Render_Alpha(pGraphicDev);

	if (m_bRenderUI_Switch == true)
	{
		Render_UI(pGraphicDev);

		Render_Pre_AlphaUI(pGraphicDev);
		Render_AlphaUI(pGraphicDev);
		Render_After_AlphaUI(pGraphicDev);
		Render_Final_AlphaUI(pGraphicDev);
	}

	Render_Scene_AlphaUI(pGraphicDev);


	if (m_bColorInversion)
		pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, prevColorArg1);

	Clear_RenderGroup();
}

void CRenderer::Clear_RenderGroup(void)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}
}

void CRenderer::Render_Priority(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_PRIORITY])
		iter->Render_GameObject();

}

void CRenderer::Render_NonAlpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_NONALPHA])
		iter->Render_GameObject();
}

void CRenderer::Render_Alpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	m_RenderGroup[RENDER_ALPHA].sort([](CGameObject* pDst, CGameObject* pSrc)->bool { return pDst->Get_ViewZ() > pSrc->Get_ViewZ();	});

	for (auto& iter : m_RenderGroup[RENDER_ALPHA])
		iter->Render_GameObject();

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CRenderer::Render_Pre_AlphaUI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (auto& iter : m_RenderGroup[RENDER_PRE_ALPHA_UI])
		iter->Render_GameObject();
}

void Engine::CRenderer::Render_AlphaUI(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_ALPHA_UI])
		iter->Render_GameObject();	
}

void Engine::CRenderer::Render_After_AlphaUI(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_AFTER_ALPHA_UI])
		iter->Render_GameObject();
}

void CRenderer::Render_Final_AlphaUI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_FINAL_UI])
		iter->Render_GameObject();

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// 아래는 다시 원래대로 되돌리는 코드
	_matrix projMatrix;
	projMatrix.PerspectiveFovLH(D3DXToRadian(60.f), (_float)WINCX / WINCY, 1.f, 1000.f);
	// 원근투영으로 바꿔줌
	_matrix* viewMatrix = nullptr;
	if (Get_Player() != nullptr)
		viewMatrix = dynamic_cast<CCamera*>(Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE))->Get_Camera_ViewMatrix();

	if (viewMatrix != nullptr)
		pGraphicDev->SetTransform(D3DTS_VIEW, viewMatrix);
	// 원근투영 적용
	// 플레이어 카메라의 뷰행렬을 디바이스에 등록

	pGraphicDev->SetRenderState(D3DRS_ZENABLE, true);
}

void CRenderer::Render_Scene_AlphaUI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	D3DXMATRIX orthoProjectionMatrix;
	D3DXMatrixOrthoLH(&orthoProjectionMatrix, (float)WINCX, (float)WINCY, 1.f, 0.f);
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &orthoProjectionMatrix);
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, false);

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (auto& iter : m_RenderGroup[RENDER_Scene_UI])
		iter->Render_GameObject();

	// 아래는 다시 원래대로 되돌리는 코드
	_matrix projMatrix;
	projMatrix.PerspectiveFovLH(D3DXToRadian(60.f), (_float)WINCX / WINCY, 1.f, 1000.f);
	// 원근투영으로 바꿔줌
	_matrix* viewMatrix = nullptr;
	if (Get_Player() != nullptr)
		viewMatrix = dynamic_cast<CCamera*>(Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE))->Get_Camera_ViewMatrix();

	if (viewMatrix != nullptr)
		pGraphicDev->SetTransform(D3DTS_VIEW, viewMatrix);
	// 원근투영 적용
	// 플레이어 카메라의 뷰행렬을 디바이스에 등록

	pGraphicDev->SetRenderState(D3DRS_ZENABLE, true);
}

void CRenderer::Render_UI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	D3DXMATRIX orthoProjectionMatrix;
	D3DXMatrixOrthoLH(&orthoProjectionMatrix, (float)WINCX, (float)WINCY, 1.f, 0.f);
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &orthoProjectionMatrix);
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, false);

	for (auto& iter : m_RenderGroup[RENDER_UI])
		iter->Render_GameObject(); 
}

void CRenderer::ToggleColorInversionFlag()
{
	m_bColorInversion = (m_bColorInversion == true) ? false : true;
}

void CRenderer::Free(void)
{
	Clear_RenderGroup();
}
