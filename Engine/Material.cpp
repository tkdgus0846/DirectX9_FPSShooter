#include "stdafx.h"
#include "Material.h"


CMaterial::CMaterial(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	ZeroMemory(&m_tMaterial, sizeof(D3DMATERIAL9));
	m_pGraphicDev->AddRef();
}


CMaterial::~CMaterial()
{
}

HRESULT CMaterial::Ready_Material(const wstring& wstrMtlPath)
{
	return parseMTLFile(wstrMtlPath);
}

HRESULT CMaterial::parseMTLFile(const wstring & wstrMtlPath)
{
\

	return S_OK;
}

CMaterial * CMaterial::Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrMtlPath)
{
	CMaterial*		pInstance = new CMaterial(pGraphicDev);

	if (FAILED(pInstance->Ready_Material(wstrMtlPath)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMaterial::Free(void)
{
	Safe_Release(m_pGraphicDev);
}
