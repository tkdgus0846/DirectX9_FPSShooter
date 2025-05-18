#include "ImManager.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"
#include "Export_Function.h"
#include "ImInspector.h"
#include "ImMenuBar.h"

IMPLEMENT_SINGLETON(CImManager)

CImManager::CImManager()
{
}

CImManager::~CImManager()
{
	Release();
}

HRESULT CImManager::Ready_IMGUI(LPDIRECT3DDEVICE9 pGraphicDev)
{
	AddContainer(L"Inspector", CImInspector::Create(pGraphicDev));
	AddContainer(L"MenuBar", CImMenuBar::Create(pGraphicDev));
	return S_OK;
}

_int CImManager::Update(_float fTimeDelta)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto& iter : m_mapImWindow)
		_int iResult = iter.second->Update(fTimeDelta);

	ImGui::EndFrame();

	return 0;
}

void CImManager::Render(LPDIRECT3DDEVICE9 pGraphicDev)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CImManager::Release()
{
	for_each(m_mapImWindow.begin(), m_mapImWindow.end(), CDeleteMap());

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

CImWindow* CImManager::FindByTag(wstring tag)
{
	auto it = m_mapImWindow.find(tag);

	if (it != m_mapImWindow.end())
		return it->second;

	return nullptr;
}

void CImManager::AddContainer(wstring key, CImWindow * pImWindow)
{
	NULL_CHECK(pImWindow);
	m_mapImWindow.insert({ key, pImWindow });
}
