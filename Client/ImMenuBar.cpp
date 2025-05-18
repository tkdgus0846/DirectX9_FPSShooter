#include "ImMenuBar.h"
#include "ImGuiFileDialog.h"
#include "Export_Function.h"
#include "FileSystem.h"

CImMenuBar::CImMenuBar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CImWindow(pGraphicDev)
{

}

CImMenuBar::~CImMenuBar()
{
}

HRESULT CImMenuBar::Ready_ImWindow()
{
	return S_OK;
}

_int CImMenuBar::Update(float fTimeDelta)
{
	// 메뉴바 생성 코드
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save", "Ctrl+S")) { m_bSaveButton = true; }
			if (ImGui::MenuItem("Load", "Ctrl+O")) { m_bLoadButton = true; }
			ImGui::Separator();
			//if (ImGui::MenuItem("Quit", "Alt+F4")) { glfwSetWindowShouldClose(window, 1); }
			ImGui::EndMenu();
		}

		// 추가적인 메뉴 항목을 여기에 작성하세요.

		ImGui::EndMainMenuBar();
	}

	if (m_bSaveButton)
		SaveFileDialog();

	if (m_bLoadButton)
		LoadFileDialog();


	return 0;
}

CImMenuBar * CImMenuBar::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CImMenuBar* pInstance = new CImMenuBar(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CImMenuBar::Free(void)
{
	__super::Free();
}

void CImMenuBar::SaveFileDialog()
{
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File"
		, ".dat,.hpp", ".", 1, nullptr
		, ImGuiFileDialogFlags_ConfirmOverwrite);

	// display
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			m_strFilePathName = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetFilePathName());
			m_strFilePath = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetCurrentPath());
			m_strFileName = CFileSystem::strToWStr(CFileSystem::FileNameFromPath(CFileSystem::wstrToStr(m_strFilePathName)));

			CFileSystem::Save(m_strFilePathName.c_str());
			m_bSaveButton = false;
			// action
		}

		// close
		ImGuiFileDialog::Instance()->Close();
	}
}

void CImMenuBar::LoadFileDialog()
{
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".dat", ".");

	// display
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			m_strFilePathName = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetFilePathName());
			m_strFilePath = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetCurrentPath());
			m_strFileName = CFileSystem::strToWStr(CFileSystem::FileNameFromPath(CFileSystem::wstrToStr(m_strFilePathName)));

			CFileSystem::Load(m_strFilePathName.c_str());
			m_bLoadButton = false;
			// action
		}

		// close
		ImGuiFileDialog::Instance()->Close();
	}
}
