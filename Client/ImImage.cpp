#include "ImImage.h"
#include "ImManager.h"
#include "Export_Function.h"
ImImage::ImImage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CImWindow(pGraphicDev)
	, m_name("Image")
{

}

ImImage::~ImImage()
{
	Safe_Release(m_pTexture);
}

_int ImImage::Update(float fTimeDelta)
{
	if (!IsEnable())
		return 0;
	
	if (m_pTexture)
	{
		if (ImGui::Begin(m_name.c_str()))
		{
			ImGui::Image((void*)m_pTexture->Get_TextureCom(), ImVec2(100.f, 100.f));
			ImGui::End();
		}
	}
}

void ImImage::Set_Texture(wstring key)
{
	Safe_Release(m_pTexture);
	m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(key.c_str(), nullptr));
}

ImImage * ImImage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	ImImage* pInstance = new ImImage(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}