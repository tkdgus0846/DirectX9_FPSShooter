#pragma once

#include "Base.h"

BEGIN(Engine)

class CMaterial : public  CBase
{
private:
	explicit CMaterial(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMaterial();

	HRESULT			Ready_Material(const wstring& wstrMtlPath);

private:
	HRESULT parseMTLFile(const wstring& wstrMtlPath);

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	D3DMATERIAL9			m_tMaterial;
	wstring					m_wstrTextureFilePath;

public:
	static CMaterial*	Create(LPDIRECT3DDEVICE9 pGraphicDev,
								wstring wstrMtlPath);

private:
	virtual void		Free(void);
};

END