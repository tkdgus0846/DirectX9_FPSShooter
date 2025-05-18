#pragma once
#include "ImWindow.h"
class ListBox :
	public CImWindow
{
private:
	ListBox(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~ListBox();
public:
	virtual HRESULT Ready_ImWindow() override;
	virtual _int Update(float fTimeDelta) override;

	_int GetCurItemIndex() {
		return selected_item;
	}

	ListBox* Create(LPDIRECT3DDEVICE9 pGraphicDev, vector<string>& vector, string name);

private:
	int selected_item = 0;
	vector<string>* items;
	string _Title;
	
};

