#pragma once
#include "Component.h"

BEGIN(Engine)

class CMesh : public CComponent
{
protected:
	explicit CMesh(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMesh(const CMesh& rhs);
	virtual ~CMesh();

public:
	HRESULT		Ready_Mesh(const _tchar * pPath);
	virtual void Render_Component() override;

protected:
	ID3DXMesh*						m_pMesh;
	vector<D3DMATERIAL9>			m_Mtrls;
	vector<IDirect3DTexture9*>		m_Textures;

protected:
	virtual void Free(void);

public:
	static CMesh*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pPath);
	virtual CComponent*		Clone(void);
};


END