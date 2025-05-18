#include "ImTest.h"
#include "ImGuiFileDialog.h"
#include "Export_Function.h"
#include "FileSystem.h"

CImTest::CImTest(LPDIRECT3DDEVICE9 pGraphicDev)
	: CImWindow(pGraphicDev)
{
	
}

CImTest::~CImTest()
{

}


HRESULT CImTest::Ready_ImWindow()
{
	return S_OK;
}

_int CImTest::Update(float fTimeDelta)
{
	// �޴��� ���� �ڵ�
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl+N")) { /* ���ο� ������ �����ϴ� �ڵ� */ }
			if (ImGui::MenuItem("Load", "Ctrl+O")) { m_bOpenButton = true; }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* ������ �����ϴ� �ڵ� */ }
			ImGui::Separator();
			//if (ImGui::MenuItem("Quit", "Alt+F4")) { glfwSetWindowShouldClose(window, 1); }
			ImGui::EndMenu();
		}

		// �߰����� �޴� �׸��� ���⿡ �ۼ��ϼ���.

		ImGui::EndMainMenuBar();
	}
	if (m_bOpenButton)
		FileDialog();



	return 0;
}

CImTest * CImTest::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CImTest* pInstance = new CImTest(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CImTest::Free(void)
{
	__super::Free();
}

void CImTest::FileDialog()
{
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");

	// display
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			m_strFilePathName = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetFilePathName());
			m_strFilePath = CFileSystem::strToWStr(ImGuiFileDialog::Instance()->GetCurrentPath());
			m_strFileName = CFileSystem::strToWStr(CFileSystem::FileNameFromPath(CFileSystem::wstrToStr(m_strFilePathName)));
			
			wstring tmp = CFileSystem::GetCurDirectory();

			m_bOpenButton = false;
			// action
		}

		// close
		ImGuiFileDialog::Instance()->Close();
	}
}

void CImTest::Save()
{

}
