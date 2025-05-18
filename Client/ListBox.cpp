#include "ListBox.h"
#include "Export_Function.h"

ListBox::ListBox(LPDIRECT3DDEVICE9 pGraphicDev)
	: CImWindow(pGraphicDev), items(nullptr)
{
	m_bEnable = true;
}


ListBox::~ListBox()
{
}

HRESULT ListBox::Ready_ImWindow()
{
	__super::Ready_ImWindow();
	FAILED_CHECK_RETURN(nullptr == items, E_FAIL);
	return S_OK;
}

_int ListBox::Update(float fTimeDelta)
{
	vector<string> items;
	if (GetEnable()) return 0;
	if (items.empty()) return 0;

	// Convert std::vector<std::string> to const char**
	vector<const char*> items_cstr;
	for (const auto& item : items)
		items_cstr.push_back(item.c_str());

	ImGui::Text(_Title.c_str());

	ImGui::ListBox("##listbox", &selected_item, items_cstr.data(), items_cstr.size(), 5);

	ImGui::Text("Selected item: %s", items[selected_item].c_str());

	return _int();
}

ListBox * ListBox::Create(LPDIRECT3DDEVICE9 pGraphicDev, vector<string>& vector, string Title)
{
	ListBox* pInstance = new ListBox(pGraphicDev);

	items = &vector;
	if (FAILED(pInstance->Ready_ImWindow()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	_Title = Title.c_str();
	return pInstance;
}