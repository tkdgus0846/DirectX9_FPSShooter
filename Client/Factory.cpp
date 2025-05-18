#include "Factory.h"
#include "FileSystem.h"

CFactory::CFactory()
{

}

CFactory::~CFactory()
{
	Release();
}

void CFactory::Register(const wstring & objectType, CreateObjectFunc createFunc)
{
	// Create함수 주소 저장.
	m_creationMap[objectType].CreateFunc = createFunc;
	m_vecWstrTag.push_back(objectType.c_str());
	m_vecStrTag.push_back(CFileSystem::wstrToStr(objectType));
}

void CFactory::ExtractTextureKey()
{
	for_each(m_creationMap.begin(), m_creationMap.end(), [this](pair<const wstring, CInfo>& entry) {
		CGameObject* p = entry.second.CreateFunc(m_pGraphicDev);
		entry.second.TextureKey = p->Get_TextureKey().c_str();

		p->Set_Flag();
		Safe_Release(p);
	});
}

HRESULT CFactory::Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;

	return S_OK;
}

void CFactory::Release()
{
	m_creationMap.clear();
	m_vecWstrTag.clear();
	m_vecStrTag.clear();
}

CGameObject * CFactory::CreateObject(const wstring & objectType)
{
	auto it = m_creationMap.find(objectType);
	if (it != m_creationMap.end())
	{
		return it->second.CreateFunc(m_pGraphicDev);
	}
	return nullptr;
}

wstring CFactory::FindTagByTextureKey(wstring TextureKey)
{
	auto it = find_if(m_creationMap.begin(), m_creationMap.end(), [&TextureKey](const pair<const wstring, CInfo>& entry)
	{
		return (0 == entry.second.TextureKey.compare(TextureKey));
	});

	if (it != m_creationMap.end())
		return it->first;

	return wstring();
}

wstring CFactory::FindTextureKeyByTag(wstring Tag)
{
	auto it = m_creationMap.find(Tag);

	if (it == m_creationMap.end())
		return wstring();

	return m_creationMap[Tag].TextureKey;
}