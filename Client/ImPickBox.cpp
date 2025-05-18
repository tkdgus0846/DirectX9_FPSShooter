#include "ImPickBox.h"
#include "ImImage.h"
#include "Factory.h"
#include "EditCamera.h"
#include "Export_Function.h"
#include "FileSystem.h"

CImPickBox::CImPickBox(LPDIRECT3DDEVICE9 pGraphicDev) :
	CImWindow(pGraphicDev)
	, m_pImage(nullptr)
	, m_pFactory(nullptr)
{
}

CImPickBox::~CImPickBox()
{
}

HRESULT CImPickBox::Ready_ImWindow()
{
	HRESULT hResult = __super::Ready_ImWindow();
	
	m_pImage = ImImage::Create(m_pGraphicDev);

	return hResult;
}

_int CImPickBox::Update(float fTimeDelta)
{
	// ÄÞº¸¹Ú½º
	vector<string> Items = m_pFactory->GetSTag();
	if (ImGui::BeginCombo("##combo", m_Item.c_str())) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < Items.size(); n++)
		{
			bool is_selected = (Items[n].compare(m_Item) == 0); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(Items[n].c_str(), is_selected))
			{
				m_Item = Items[n];

				m_pImage->Set_Texture(m_pFactory->FindTextureKeyByTag(TO_WSTR(m_Item)));
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
		}
		ImGui::EndCombo();
	}
	
	if (m_Item == "a")
		return _int();
	
	m_pImage->Set_Texture(m_pFactory->FindTextureKeyByTag(TO_WSTR(m_Item)));
	m_pImage->Update(fTimeDelta);
	
	return _int();
}

CImPickBox * CImPickBox::Create(LPDIRECT3DDEVICE9 pGraphicDev, string name, CFactory * pFactory)
{
	CImPickBox* pInstance = new CImPickBox(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	pInstance->Set_Name(name);
	pInstance->Set_Factory(pFactory);

	return pInstance;
}

void CImPickBox::Free()
{
	Safe_Release(m_pImage);
	__super::Free();
}