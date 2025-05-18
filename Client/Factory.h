#pragma once

#include "Include.h"
#include "GameObject.h"

// 클래스가 가지는 고유한 정보를 저장함.
typedef CGameObject* (*CreateObjectFunc)(LPDIRECT3DDEVICE9);
typedef struct tagClassInfo
{
	CreateObjectFunc	CreateFunc;
	wstring				TextureKey;
}ClassInfo, CInfo;

class CFactory
{
protected:
	CFactory();
	virtual ~CFactory();

	virtual HRESULT Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev);

	virtual void Release();

protected:
	virtual void Register(const wstring& objectType, CreateObjectFunc createFunc);
	void ExtractTextureKey();

public:
	CGameObject*	CreateObject(const wstring& objectType);
	wstring			FindTagByTextureKey(wstring				TextureKey);
	wstring			FindTextureKeyByTag(wstring Tag);

	const vector<wstring>& GetWTag() { return m_vecWstrTag; }
	const vector<string>& GetSTag() { return m_vecStrTag; }

protected:
	map<wstring, CInfo> m_creationMap;
	vector<wstring> m_vecWstrTag;
	vector<string>	m_vecStrTag;
	LPDIRECT3DDEVICE9 m_pGraphicDev;
};