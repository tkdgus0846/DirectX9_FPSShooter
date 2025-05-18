#pragma once
#include "ImWindow.h"
#include "Texture.h"

class CImManager;

class ImImage :
	public CImWindow
{
	friend CImManager;
public:
	ImImage(LPDIRECT3DDEVICE9 pGraphicDev);
	~ImImage();

public:
	virtual _int Update(float fTimeDelta) override;

public:
	void	Set_Texture(wstring key);
	void	Set_Name(string str) { m_name = str.c_str(); }
	static ImImage* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CTexture* m_pTexture;
	string	m_name;
};